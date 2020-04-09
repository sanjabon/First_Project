#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int RedChannel(){
	string loc, dest;
	cout<<"Welcome to RedChannel, This by default Takes Source Video named Sample.avi and stores redChannel Video as newVid.avi on same folder";
	cout<<"Enter relative path or absolute path of video(Already Stored)";
	cin>>loc;
	VideoCapture Vid(loc);
	if(Vid.isOpened()==false){
		cout<<"Unable to Load video\n";
		cin.get();
		return -1;
	}
	int w= (Vid.get(CAP_PROP_FRAME_WIDTH));
	int h= (Vid.get(CAP_PROP_FRAME_HEIGHT));
	Size s(w,h);
	int fps=Vid.get(CAP_PROP_FPS);
	cout<<"Enter relative path or absolute path of video(to be stored)";
	cin>>dest;
	VideoWriter redVid(dest, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, s, true);
	if(redVid.isOpened()==false){
		cout<<"Video writed failed\n";
		cin.get();
		return -1;
	}
	cout<<"\nEnter Size(in seconds) of desired Video: ";
	int x;
	cin>>x;
	cout<<"You can press escape(ESC) to stop in real time\n";
	int i=0, n=fps*x;
	string winname="RECHANNEL";
	namedWindow(winname);
	while(i<n){
		i++;
		Mat frame;
		int check= Vid.read(frame);
		if(!check){
			break;
		}
		//cout<<"Here\n";
		vector <Mat> sepframe;
		split(frame, sepframe );
		sepframe[1]=Mat::zeros(s, sepframe[0].type());
		sepframe[0]=Mat::zeros(s, sepframe[0].type());
		Mat res;
		merge(sepframe, res);
		redVid.write(res);
		imshow(winname, res);
		if(waitKey(10)==27){
			break;}
	}
	cout<<"\n!!!SUCCESS!!!\n";
	destroyAllWindows();
	return 0;
}
int recvid(){
	int x;
	string loc, dest;
	cout<<"\n\nWelcome to this Module\n Due to unavailibilty of webcam, I uses stored video in this. vid(0) can be used for desired output\n";
	cout<<"Do you have webcam?1/0 ";
	cin>>x;
	VideoCapture vid;
	if(x){
		vid= VideoCapture(0);
	}
	else{
		cout<<"Enter relative path or absolute path of video(Stored video)";
		cin>>loc;
		vid= VideoCapture(loc);
	}
	if(vid.isOpened()<=0){
		cout<<"Video Load failed\n";
		cin.get();
		return -1;
	}
	
	int w= (vid.get(CAP_PROP_FRAME_WIDTH));
	int h=  (vid.get(CAP_PROP_FRAME_HEIGHT));
	Size s(w,h);
	int fps=vid.get(CAP_PROP_FPS);
	cout<<"Enter relative path or absolute path of video(to be stored)";
	cin>>dest;
	VideoWriter vW(dest, VideoWriter::fourcc('M','J', 'P', 'G'), fps, s, true);
	if(vW.isOpened()<=0){
		cout<<"Video Writer Failed to Open\n Make sure you typed supported extension video file";
		cin.get();
		return -1;
		}
	int i=0, t=10*fps;
	
	while(i<t){
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
	cout<<"\n!!!SUCCESS!!!\n";
	return 0;
}

int blurvid(){
	cout<<"welcome to GaussianBlur\n";
	string loc, dest;
	cout<<"Enter relative path or absolute path of video(stored Video)";
	cin>>loc;
	VideoCapture Vid(loc);
	if(Vid.isOpened()==false){
		cout<<"Vedio Capture Failed.. \nExiting...";
		return -1;
		}
	Size S( Vid.get(CAP_PROP_FRAME_WIDTH), Vid.get(CAP_PROP_FRAME_HEIGHT));
	int fps=Vid.get(CAP_PROP_FPS);
	cout<<"Enter relative path or absolute path of video(to be stored)";
	cin>>dest;
	VideoWriter blurvid(dest, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, S, true);
	if(blurvid.isOpened()==false){
		cout<<"Failed to open";
		return -1;
		}
	int t;
	cout<<"\nEnter time in seconds: ";
	cin>>t;
	t=t*fps;
	int i=0, k;
	cout<<"\nEnter Kernel size(odd) high for more blur and low for less blur(Must be odd and in pixel range)";
	cin>>k;
	while(i<t){
		Mat frame;
		i++;
		if(Vid.read(frame)){
			GaussianBlur(frame, frame, Size(k, k), 0);
			blurvid.write(frame);
			
			}
		else{
			cout<<"Video Ended \n";
			return 1;
			}
		
		}
	cout<<"Completed Capture of "<<i<<"Frames";
	cout<<"\n!!!SUCCESS!!!\n";
	return 0;
}

int security(){
string user, pass;

cout<<"We are inkers, Our goal is to take the security to next level";
int attempt=5;
while(attempt){
	cout<<"\n Enter Username:";
	cin>>user;
	cout<<"\n Enter password:";
	cin>>pass;
	if(user=="INKERS" && pass=="1234"){
		cout<<"Success\n";
		return 1;
		}
	attempt--;
	if(attempt){
		cout<<"Wrong Match, Attempts Left="<<attempt;
		cout<<"\n TRY AGAIN\n";
		}
	}
cout<<"Login failed\n";
return -1;
}

int main(){
bool x=true;
int choice, tight_security=1;
cout<<"Namaste Sir, One more task is there to store the file, but gaussian blur, recording 10sec video and redchannel save the recorded file\n";
while(x){
	cout<<"\n\nMenu Driven Program: \n1. simple login-logout feature \n2. Record a short 10-second video from the webcam \n3. Extract the red channel from the frames \n4. add a gaussian filter to these frames\n Any other Key to Exit\n";
	cin>>choice;
	switch(choice){
		case 1: 
				if(tight_security){
					security();
					tight_security=0;
					}
				else{
					cout<<"Sir if Do that Again, That will be security breech, Sorry. We Don't Do there here";
					}
				break;
		case 2: 
				recvid();
				break;
		case 3: 
				RedChannel();			
				break;
		case 4: 
				blurvid();
				break;
		default: x=0;
		}
}
cout<<"To be honest I was really unaware of this cool stuff, Thanks for introducing it to me :)";
return 0;
}
