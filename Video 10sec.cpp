#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(){
	VideoCapture vid("Sample.avi");
	if(vid.isOpened()<=0){
		cout<<"Video Load failed\n";
		cin.get();
		return -1;
	}
	
	int w= (vid.get(CAP_PROP_FRAME_WIDTH));
	int h=  (vid.get(CAP_PROP_FRAME_HEIGHT));
	Size s(w,h);
	int fps=vid.get(CAP_PROP_FPS);
	VideoWriter vW("VIDEOdone.avi", VideoWriter::fourcc('M','J', 'P', 'G'), fps, s, true);
	if(vW.isOpened()<=0){
		cout<<"Video Writer Failed to Open\n";
		cin.get();
		return -1;
		}
	int i=0;
	while(i<240){
			i++;
			Mat oneFrame;
			bool check=vid.read(oneFrame);
			if(!check){
				cout<<"something went wrong\n";
				cin.get();
				break;
			}
			vW.write(oneFrame);
	}
	cout<<"SuccessFul\n";
	return 0;
}
