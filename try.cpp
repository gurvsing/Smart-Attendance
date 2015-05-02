/*
 * Copyright (c) 2011. Philipp Wagner <bytefish[at]gmx[dot]de>.
 * Released to public domain under terms of the BSD Simplified license.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the organization nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *   See <http://www.opensource.org/licenses/bsd-license>
 */

#include "opencv2/core/core.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
 #include <utility>
#include <vector>
#include <stdio.h>
#include <time.h>

 #define BUG cout<<"BUG\n";

using namespace cv;
using namespace std;

CascadeClassifier face_cascade;
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%X", &tstruct);

    return buf;
}

int differ(string a, string b)
{
    long long int c,d;

    c=(((((a[0]-'0')*10)+(a[1]-'0'))*60*60) + ((((a[3]-'0')*10)+(a[4]-'0'))*60) + (((a[6]-'0')*10)+(a[7]-'0'))) ;
    d=(((((b[0]-'0')*10)+(b[1]-'0'))*60*60) + ((((b[3]-'0')*10)+(b[4]-'0'))*60) + (((b[6]-'0')*10)+(b[7]-'0'))) ;
    //cout<<c<<"*"<<d<<"*"<<endl;
    return (c-d);
}

static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    Mat testSample = Mat ( 255 , 255 , CV_8UC1 );
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
           // cout<<"path and classlabel"<<path<<classlabel;
            Mat grayscaleFrame = imread(path, 0);
            equalizeHist(grayscaleFrame, grayscaleFrame);
            std::vector<Rect> faces;
            face_cascade.detectMultiScale(grayscaleFrame,faces,1.1,2,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(30,30));

            for(size_t i=0;i<faces.size();i++)  
            {
                //ellipse (captureFrame,center,Size(faces[i].width*0.5,faces[i].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
                //Rect facerect(faces[i].x - 20,faces[i].y- 20,faces[i].width + 20,faces[i].height+ 20);
                Mat Roi = grayscaleFrame(faces[i]);
                resize ( Roi , testSample , testSample.size());
                imshow(string("Cropped ") + classlabel,testSample);
                waitKey(10);
                images.push_back(testSample.clone());
                labels.push_back(atoi(classlabel.c_str()));
            }
        }
    }
    cout << images.size() << " "  << labels.size() << " " << images[0].size().width <<  " x " << images[0].size().height;
}

int main(int argc, const char *argv[]) {
    vector <pair <string, string> >  values[10];

    pair <string, string> check[10];
    for(int i=0;i<10;i++)
    {
        check[i].first=check[i].second="\0";
    }
    int label;
    // Check for valid command line arguments, print usage
    // if no arguments were given.
    map <int, string> rec_op;
    rec_op[0]  = "s5";
    rec_op[1]  = "s4";
    rec_op[2]  = "s6";
    rec_op[3]  = "s1";
    rec_op[4]  = "s7";
    rec_op[5]  = "s3";
    rec_op[6]  = "s2";
    
   
    VideoCapture stream1(1);
    Mat captureFrame;
    face_cascade.load("haarcascade_frontalface_alt.xml");
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <csv.ext> <output_folder> " << endl;
        exit(1);
    }
    string output_folder = ".";
    if (argc == 3) {
        output_folder = string(argv[2]);
    }
    // Get the path to your CSV.
    string fn_csv = string(argv[1]);
    // These vectors hold the images and corresponding labels.
    vector<Mat> images;
    vector<int> labels;
    // Read in the data. This can fail if no valid
    // input filename is given.
    //BUG;
    try {
        read_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    BUG;
    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }
    // Get the height from the first image. We'll need this
    // later in code to reshape the images to their original
    // size:
    int height = images[0].rows;
    // The following lines simply get the last images from
    // your dataset and remove it from the vector. This is
    // done, so that the training data (which we learn the
    // cv::FaceRecognizer on) and the test data we test
    // the model with, do not overlap.
    Mat testSample = images[images.size() - 2];
    int testLabel = labels[labels.size() - 2];
	//cout<<images.size();
    images.pop_back();
    labels.pop_back();
    // The following lines create an Eigenfaces model for
    // face recognition and train it with the images and
    // labels read from the given CSV file.
    // This here is a full PCA, if you just want to keep
    // 10 principal components (read Eigenfaces), then call
    // the factory method like this:
    //
    //      cv::createEigenFaceRecognizer(10);
    //
    // If you want to create a FaceRecognizer with a
    // confidence threshold (e.g. 123.0), call it with:
    //
    //      cv::createEigenFaceRecognizer(10, 123.0);
    //
    // If you want to use _all_ Eigenfaces and have a threshold,
    // then call the method like this:
    //
    //      cv::createEigenFaceRecognizer(0, 123.0);
    //
    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
    model->train(images, labels);
    // The following line predicts the label of a given
    // test image:
    int predictedLabel = model->predict(testSample);
    //
    // To get the confidence of a prediction call the model with:
    //
    //      int predictedLabel = -1;
    //      double confidence = 0.0;
    //      model->predict(testSample, predictedLabel, confidence);
    //
    string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
    cout << result_message << endl;
    // Here is how to get the eigenvalues of this Eigenfaces model:
    Mat eigenvalues = model->getMat("eigenvalues");
    // And we can do the same to display the Eigenvectors (read Eigenfaces):
    Mat W = model->getMat("eigenvectors");
    // Get the sample mean from the training data
    Mat mean = model->getMat("mean");
    // Display or save:
    if(argc == 2) {
        //imshow("mean", norm_0_255(mean.reshape(1, images[0].rows)));
    } else {
        imwrite(format("%s/mean.png", output_folder.c_str()), norm_0_255(mean.reshape(1, images[0].rows)));
    }
    // Display or save the Eigenfaces:
    for (int i = 0; i < min(10, W.cols); i++) {
        string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
        cout << msg << endl;
        // get eigenvector #i
        Mat ev = W.col(i).clone();
        // Reshape to original size & normalize to [0...255] for imshow.
        Mat grayscale = norm_0_255(ev.reshape(1, height));
        // Show the image & apply a Jet colormap for better sensing.
        Mat cgrayscale;
        applyColorMap(grayscale, cgrayscale, COLORMAP_JET);
        // Display or save:
        if(argc == 2) {
            //imshow(format("eigenface_%d", i), cgrayscale);
        } else {
            imwrite(format("%s/eigenface_%d.png", output_folder.c_str(), i), norm_0_255(cgrayscale));
        }
    }

    // Display or save the image reconstruction at some predefined steps:
    for(int num_components = min(W.cols, 10); num_components < min(W.cols, 300); num_components+=15) {
        // slice the eigenvectors from the model
        Mat evs = Mat(W, Range::all(), Range(0, num_components));
        Mat projection = subspaceProject(evs, mean, images[0].reshape(1,1));
        Mat reconstruction = subspaceReconstruct(evs, mean, projection);
        // Normalize the result:
        reconstruction = norm_0_255(reconstruction.reshape(1, images[0].rows));
        // Display or save:
        if(argc == 2) {
            //imshow(format("eigenface_reconstruction_%d", num_components), reconstruction);
        } else {
            imwrite(format("%s/eigenface_reconstruction_%d.png", output_folder.c_str(), num_components), reconstruction);
        }
    }
    // Display if we are not writing to an output folder:
    if(argc == 2) {
        //waitKey(0);


    
    Mat grayscaleFrame , croppedImage;
    while(true)
    {
        stream1.read(captureFrame);
        cvtColor(captureFrame,grayscaleFrame,CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
        std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleFrame,faces,1.1,2,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(30,30));

        for(size_t i=0;i<faces.size();i++)  
        {
            Point center(faces[i].x + faces[i].width*0.5,faces[i].y+faces[i].height*0.5);
            ellipse (captureFrame,center,Size(faces[i].width*0.5,faces[i].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
            //Rect facerect(faces[i].x - 20,faces[i].y- 20,faces[i].width + 20,faces[i].height+ 20);
            Rect facerect(faces[i].x ,faces[i].y,faces[i].width ,faces[i].height);
            croppedImage=captureFrame(facerect);
            Mat Roi =grayscaleFrame(faces[i]);
            resize ( Roi , testSample , testSample.size()) ;
            int predictedLabel = model->predict(testSample);
            label=predictedLabel;
           string box_text;
            if(check[label].first=="\0")
             {
            check[label].first = currentDateTime(); 
            check[label].second = "\0";
            box_text=format("IN %s",rec_op[predictedLabel].c_str());
            }
            else 
            {
            check[label].second = currentDateTime();
                if(differ(check[label].second,check[label].first)>15)
                {
                values[label].push_back(make_pair(check[label].first,check[label].second));
                cout<<check[label].first<<endl<<check[label].second;
                check[label].first = "\0";
                check[label].second = "\0";
                box_text=format("OUT %s",rec_op[predictedLabel].c_str());
                }
                else
                    box_text=format("%s",rec_op[predictedLabel].c_str());
                
            }
                    imshow("Cropped",testSample);
                    Rect face_i=faces[i];
                    int pos_x = std::max(face_i.tl().x - 10, 0);
                    int pos_y = std::max(face_i.tl().y - 10, 0);
                    // And now put it into the image:
                    
                    putText(captureFrame, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(255,0,0), 2.0);
                }

        imshow("output",captureFrame);

        if (cv::waitKey(30) >= 0)
        {
            
            break;
        }
    }
    cv::destroyAllWindows();
// And get a prediction from the cv::FaceRecognizer:
}
        int i,j;
        ofstream myfile;
        myfile.open ("data.txt");
        int N=9;
        myfile<<N<<endl;
        for(i=0;i<N;i++)
        {
            myfile<<rec_op[i]<<endl;
        }
        for(i=0;i<N;i++)
        {
            int velen=values[i].size();
            myfile<<velen<<endl;
            for(j=0;j<velen;j++)
            {
                myfile<<values[i][j].first<<" "<<values[i][j].second<<endl;
            }
        }
        myfile.close();
    return 0;
}
