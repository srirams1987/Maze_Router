
#include "Maze.h"





UI::UI(int r,int c){
		rows = r;
		cols = c;
		Img = Mat::zeros(r*100+1,c*100+1,CV_8UC3);
		for(int i=1;i<=r;i++)
			for(int j=1;j<=c;j++)
				{

					line(Img,Point(i*100,0),Point(i*100,(c+1)*100),CV_RGB(255,255,255),2,8,0);
					line(Img,Point(0,j*100),Point((r+1)*100,j*100),CV_RGB(255,255,255),2,8,0);
					//PE_cells[i*r + j] = Img(Range(i,i+100),Range(j,j+100));
					//imshow()
					}

		}

UI::~UI(){

	}
	
void UI::DispInit(vector<Point> Src)
	{
		this->Init = Src;
		for(int k=0;k<Src.size();k++){
			
			Point start = Point((Src[k].x)*100,(Src[k].y)*100);
			Point end = Point((Src[k].x+1)*100,(Src[k].y+1)*100);
			
			Mat img = Img(Range(start.x,end.x),Range(start.y,end.y));
		
			for(int i=0;i<img.rows;i++)
			for(int j=0;j<img.cols;j++)
			{
				if(k==0){
				img.at<Vec3b>(i,j).val[0] = 255;img.at<Vec3b>(i,j).val[1] = 0;img.at<Vec3b>(i,j).val[2] = 0;
				//continue;
				}
				else if(k==1){
				img.at<Vec3b>(i,j).val[0] = 0;img.at<Vec3b>(i,j).val[1] = 255;img.at<Vec3b>(i,j).val[2] = 0;
				//continue;
				}
				else{
				img.at<Vec3b>(i,j).val[0] = 255;
				img.at<Vec3b>(i,j).val[1] = 255;
				img.at<Vec3b>(i,j).val[2] = 255;
				}
				
							
			}
			if(k==0)
			putText(Img,"Source",Point(start.y+20,start.x+20),   FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);
			
			else if(k==1)
			putText(Img,"Target",Point(start.y+20,start.x+20),   FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);
			
			else 
			putText(Img,"Blocked",Point(start.y+20,start.x+20),   FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,0), 1, CV_AA);
		}
		imshow("MAZE ROUTER GUI ",Img);
		waitKey(0);
	}
	
void UI::update(Point P,bool flag[4],int R,string Stage)
		{
			//P = P + Point(1,1);
			string wave = "Wave";
			string Trace = "TraceBack";
			Point start = Point((P.x)*100,(P.y)*100);
			Point end = Point((P.x+1)*100,(P.y+1)*100);
			//cout<<"start "<<start.x<<","<<start.y<<" end "<<end.x<<","<<end.y<<endl;
			Mat img = Img(Range(start.x,end.x),Range(start.y,end.y));//[Src[k].x*rows + Src[k].y];
			uchar F=0;
			F |= (flag[0]==true) <<1;
			F |= (flag[1]==true) <<1;
			F |= (flag[2]==true) <<1;
			F |= (flag[3]==true) <<1;
		//	cout<<int(F)<<endl;
			string g;
			if(flag[0])g="N";else g="0";
			if(flag[1])g=g+"W";else g=g+"0";
			if(flag[2])g=g+"E";else g=g+"0";
			if(flag[3])g=g+"S";else g=g+"0";
			for(int i=0;i<img.rows;i++)
			for(int j=0;j<img.cols;j++)
			{
				
				if(strcmp(Stage.c_str(),wave.c_str())==0)
				{
					img.at<Vec3b>(i,j).val[0] = 255;img.at<Vec3b>(i,j).val[1] = 0;img.at<Vec3b>(i,j).val[2] = 255;
				}

				if(strcmp(Stage.c_str(),Trace.c_str())==0)
				{
					img.at<Vec3b>(i,j).val[0] = 125;img.at<Vec3b>(i,j).val[1] = 125;img.at<Vec3b>(i,j).val[2] = 125;
				}
								
			}
		//putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness=1, int lineType=8, bool bottomLeftOrigin=false)
		string s; stringstream ss;ss<<R;
		if(strcmp(Stage.c_str(),wave.c_str())==0){
			
			s = "Label "+ ss.str();
			
		putText(Img,s.c_str(),Point(start.y+20,start.x+20),   FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);
		ss.str()="";ss<<int(F);
		string S = ss.str();
		putText(Img,g.c_str(),Point(start.y+20,start.x+40),   FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);
		}
		if(strcmp(Stage.c_str(),Trace.c_str())==0){
		putText(Img,"Path",Point(start.y+20,start.x+20),   FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);}
		
			for(int i=1;i<=rows;i++)
			for(int j=1;j<=cols;j++)
				{
					
					line(Img,Point(i*100,0),Point(i*100,(cols+1)*100),CV_RGB(255,255,255),2,8,0);
					line(Img,Point(0,j*100),Point((rows+1)*100,j*100),CV_RGB(255,255,255),2,8,0);
					//PE_cells[i*r + j] = Img(Range(i,i+100),Range(j,j+100));
					//imshow()
					}
				
		
			imshow("MAZE ROUTER GUI ",Img);
			waitKey(10);
			
		}		
	
void UI::ShowJustPath(vector<Point> Src)
{
		Img = Mat::zeros(rows*100+1,cols*100+1,CV_8UC3);
		DispInit(this->Init);
		for(int k=0;k<Src.size();k++)
		{
			
			Point start = Point((Src[k].x)*100,(Src[k].y)*100);
			Point end = Point((Src[k].x+1)*100,(Src[k].y+1)*100);
				
			Mat img = Img(Range(start.x,end.x),Range(start.y,end.y));
			
			for(int i=0;i<img.rows;i++)
			for(int j=0;j<img.cols;j++)
			{
					img.at<Vec3b>(i,j).val[0] = 125;
					img.at<Vec3b>(i,j).val[1] = 125;
					img.at<Vec3b>(i,j).val[2] = 125;
								
					}
			putText(Img,"Path",Point(start.y+20,start.x+20),   FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);		
		}
			
			
			for(int i=1;i<=rows;i++)
			for(int j=1;j<=cols;j++)
				{
					
					line(Img,Point(i*100,0),Point(i*100,(cols+1)*100),CV_RGB(255,255,255),2,8,0);
					line(Img,Point(0,j*100),Point((rows+1)*100,j*100),CV_RGB(255,255,255),2,8,0);
					
					}
		imshow("MAZE ROUTER GUI ",Img);
		waitKey(0);	
}	
