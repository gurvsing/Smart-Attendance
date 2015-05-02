#include <iostream>

#include <fstream>
#include <sstream>
#include <string.h>
#include <ctype.h>

#include "opencv2/core/core.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"




using namespace std;
using namespace cv;
int main()
{
	CascadeClassifier face_cascade;
face_cascade.load("haarcascade_frontalface_alt.xml");
	int i=0,j,limit=50;
	string dir,dir3,expr,enter,csv=".csv";
	string dir2="mkdir ";
	VideoCapture stream1(1);

	if(!stream1.isOpened())
	{
		cout<< "\nCannot open camera\n";
		exit(0);
	}
	cout<<" \nEnter your name ";
	cin>>dir;
	dir3=dir2+dir;
	enter=enter+dir;
//cout<<dir3;
//system(dir3.c_str());
//waitKey(0);
//expr=dir2+format("%s/happy",dir.c_str());
	system(expr.c_str());
	expr=dir2+format("Facerec/%s",dir.c_str());
	system(expr.c_str());
	
	//cout<<"You";
	//cin>>j;

	//Happy
	i=0;
	while(i<=4)
	{

	
	while(true)
	{
		
		Mat image,grayscaleFrame,copy;
		// waitKey(0);

		stream1.read(image);
		copy=image.clone();
		cvtColor(image,grayscaleFrame,CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
		std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleFrame,faces,1.1,2,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(30,30));

        for(size_t l=0;l<faces.size();l++)  
        {
            Point center(faces[l].x + faces[l].width*0.5,faces[l].y+faces[l].height*0.5);
            ellipse (image,center,Size(faces[l].width*0.5,faces[l].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
        }
        imshow("Happy",image);
		if (cv::waitKey(30) >= 0)
    	{
      		cv::imwrite(format("Facerec/%s/Happy(%d).png",dir.c_str(),i), copy);
      		break;
    	}
    	
	}
		cout<<"Happy "<<i+1<<endl;
      	i++;
    }
    cv::destroyAllWindows();

	//Sad
	i=0;
	while(i<=4)
	{

	
	while(true)
	{
		
		Mat image,grayscaleFrame,copy;
		// waitKey(0);

		stream1.read(image);
		copy=image.clone();
		cvtColor(image,grayscaleFrame,CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
		std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleFrame,faces,1.1,2,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(30,30));

        for(size_t l=0;l<faces.size();l++)  
        {
            Point center(faces[l].x + faces[l].width*0.5,faces[l].y+faces[l].height*0.5);
            ellipse (image,center,Size(faces[l].width*0.5,faces[l].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
        }
		imshow("Sad",image);

		if (cv::waitKey(30) >= 0)
    	{
      		cv::imwrite(format("Facerec/%s/Sad(%d).png",dir.c_str(),i), copy);
      		break;
    	}
    	
	}
		cout<<"Sad "<<i+1<<endl;
      	i++;
    }
    cv::destroyAllWindows();

    //Left
	i=0;
	while(i<=4)
	{

	
	while(true)
	{
		
		Mat image,grayscaleFrame,copy;
		// waitKey(0);

		stream1.read(image);
		copy=image.clone();
		cvtColor(image,grayscaleFrame,CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
		std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleFrame,faces,1.1,2,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(30,30));

        for(size_t l=0;l<faces.size();l++)  
        {
            Point center(faces[l].x + faces[l].width*0.5,faces[l].y+faces[l].height*0.5);
            ellipse (image,center,Size(faces[l].width*0.5,faces[l].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
        }
		imshow("Left",image);

		if (cv::waitKey(30) >= 0)
    	{
      		cv::imwrite(format("Facerec/%s/Left(%d).png",dir.c_str(),i), copy);
      		break;
    	}
    	
	}
		cout<<"Left "<<i+1<<endl;
      	i++;
    }
    cv::destroyAllWindows();

    //Right
	i=0;
	while(i<=4)
	{

	
	while(true)
	{
		
		Mat image,grayscaleFrame,copy;
		// waitKey(0);

		stream1.read(image);
		copy=image.clone();
		cvtColor(image,grayscaleFrame,CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
		std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleFrame,faces,1.1,2,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(30,30));

        for(size_t l=0;l<faces.size();l++)  
        {
            Point center(faces[l].x + faces[l].width*0.5,faces[l].y+faces[l].height*0.5);
            ellipse (image,center,Size(faces[l].width*0.5,faces[l].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
        }
		imshow("Right",image);

		if (cv::waitKey(30) >= 0)
    	{
      		cv::imwrite(format("Facerec/%s/Right(%d).png",dir.c_str(),i), copy);
      		break;
    	}
    	
	}
		cout<<"Right "<<i+1<<endl;
      	i++;
    }
    cv::destroyAllWindows();

    //UP
	i=0;
	while(i<=4)
	{

	
	while(true)
	{
		
		Mat image,grayscaleFrame,copy;
		// waitKey(0);

		stream1.read(image);
		copy=image.clone();
		cvtColor(image,grayscaleFrame,CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
		std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleFrame,faces,1.1,2,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(30,30));

        for(size_t l=0;l<faces.size();l++)  
        {
            Point center(faces[l].x + faces[l].width*0.5,faces[l].y+faces[l].height*0.5);
            ellipse (image,center,Size(faces[l].width*0.5,faces[l].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
        }
		imshow("UP",image);

		if (cv::waitKey(30) >= 0)
    	{
      		cv::imwrite(format("Facerec/%s/UP(%d).png",dir.c_str(),i), copy);
      		break;
    	}
    	
	}
		cout<<"UP "<<i+1<<endl;
      	i++;
    }
    cv::destroyAllWindows();

    //Down
	i=0;
	while(i<=4)
	{

	
	while(true)
	{
		
		Mat image,grayscaleFrame,copy;
		// waitKey(0);

		stream1.read(image);
		copy=image.clone();
		cvtColor(image,grayscaleFrame,CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
		std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleFrame,faces,1.1,2,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(30,30));

        for(size_t l=0;l<faces.size();l++)  
        {
            Point center(faces[l].x + faces[l].width*0.5,faces[l].y+faces[l].height*0.5);
            ellipse (image,center,Size(faces[l].width*0.5,faces[l].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);
        }
		imshow("Down",image);

		if (cv::waitKey(30) >= 0)
    	{
      		cv::imwrite(format("Facerec/%s/Down(%d).png",dir.c_str(),i), copy);
      		break;
    	}
    	
	}
		cout<<"Down "<<i+1<<endl;
      	i++;
    }
    cv::destroyAllWindows();




cout<<" Done ";

return 0;
}