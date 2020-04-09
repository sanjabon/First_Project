#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;
int main(){
	VideoCapture Vid("rose.avi");
	if(Vid.isOpened()==false){
		cout<<"Unable to Load video\n";
		cin.get();
		return -1;
	}
	int w= (Vid.get(CAP_PROP_FRAME_WIDTH));
	int h=  (Vid.get(CAP_PROP_FRAME_HEIGHT));
	Size s(w,h);
	int fps=Vid.get(CAP_PROP_FPS);
	VideoWriter redVid("RedChannel.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, s, true);
	if(redVid.isOpened()==false){
		cout<<"Video writed failed\n";
		cin.get();
		return -1;
	}
	int i=0, n=fps*20;
	while(i<n){
		i++;
		Mat frame;
		int check= Vid.read(frame);
		if(!check){
			cout<<"Video ended it seems\n";
			cin.get();
			return -1;
		}
		//cout<<"Here\n";
		vector <Mat> sepframe;
		split(frame, sepframe );
		sepframe[1]=Mat::zeros(s, sepframe[0].type());
		sepframe[0]=Mat::zeros(s, sepframe[0].type());
		Mat res;
		merge(sepframe, res);
		redVid.write(res);
		if(waitKey(10)==27){
			break;}

	}
	cout<<"Success\n";
	return 0;
}
