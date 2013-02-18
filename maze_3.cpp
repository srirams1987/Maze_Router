
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
#include <list>
#include <deque>



class UI{
	private:
	int rows,cols;
	vector<Mat> PE_cells;
	Mat Img;
	vector<Point> Init;
	public:
	UI(int r,int c){
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
	~UI(){
		
		}
	
	void DispInit(vector<Point> Src)
	{
		this->Init = Src;
		for(int k=0;k<Src.size();k++){
			
			Point start = Point((Src[k].x)*100,(Src[k].y)*100);
			Point end = Point((Src[k].x+1)*100,(Src[k].y+1)*100);
			//cout<<"start "<<start.x<<","<<start.y<<" end "<<end.x<<","<<end.y<<endl;
			Mat img = Img(Range(start.x,end.x),Range(start.y,end.y));//[Src[k].x*rows + Src[k].y];
		
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
		
		void update(Point P,bool flag[4],int R,string Stage)
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
		
		void ShowJustPath(vector<Point> Src)
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
			
			//cvDestroyAllWindows();
			for(int i=1;i<=rows;i++)
			for(int j=1;j<=cols;j++)
				{
					
					line(Img,Point(i*100,0),Point(i*100,(cols+1)*100),CV_RGB(255,255,255),2,8,0);
					line(Img,Point(0,j*100),Point((rows+1)*100,j*100),CV_RGB(255,255,255),2,8,0);
					//PE_cells[i*r + j] = Img(Range(i,i+100),Range(j,j+100));
					//imshow()
					}
		imshow("MAZE ROUTER GUI ",Img);
			waitKey(0);	
			}
	
	};





typedef enum state{ Source, Block, Label, Target, Idel,Trace};
typedef struct PE
{
	state S;
	int R;
	bool NS;
	Point TraceBack;
	bool flag[4];
	PE(){
		S = Idel;
		R =0;
		TraceBack = Point(0,0);
		flag[0]=false;flag[1]=false;flag[1]=false;flag[3]=false;
		NS = false;
		}
	};

int main(int argc, char *argv[] )
{
	/*if(argc < 2)
	{
		cout<<"Usage ./maze <parameters.txt> ";
		}
		* */
	
	deque<int> a;
	
	a.push_back(0);
	
	cout<<a[0]<<endl;
	
	
	
	
	
	int rows = 7;
	int cols = 7;
	vector<Point>P;
	Point source= Point(0,0)	;
	Point target= Point(6,5)	;
	//ProcessingElement PE;
	//Point source= Point(1,1)	;
	//Point target= Point(5,5)	;
	P.push_back(source);
	P.push_back(target);
	//P.push_back(Point(3,3));
	P.push_back(Point(4,4));
	P.push_back(Point(0,5));
	P.push_back(Point(1,5));
	//P.push_back(Point(3,5));
	vector<PE> Grid(rows*cols);
	Grid[source.x*cols+source.y].S = Source;
	Grid[target.x*cols+target.y].S = Target;
	for(int i=2;i<P.size();i++)
	{
		
		int idx = P[i].x*cols+P[i].y;
		cout<<P[i].x<<","<<P[i].y<<","<<idx<<endl;
		Grid[idx].S = Block;
	}

			for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++){
				cout<<i<<","<<j<<" "<<Grid[i*cols + j].S<<endl;
							
				}



	UI ui(rows,cols);
	ui.DispInit(P);
	bool TargetReached = false;
	int R = 0;
	int tarI=0,tarJ=0;
	int i_k = 0,j_k = 0;
	bool out=false;
	cout<<"rows "<<rows<<" cols "<<cols<<endl;
	//Point node = source
	bool first = true;vector<Point> label;
	while(!TargetReached)
	{
		cout<<"Radius "<<R<<" T "<<TargetReached<<endl;
		bool update=false;
		//cout<<i<<","<<j<<endl;
		if(out) break;
		//findBlocksWithRadius(R, Grid)
		
		vector<Point>L;
		if(first) {label.push_back(source); first=false;}
		for(int l=0;l<label.size();l++)
		{
			Point node = label[l];
			for(int i = node.x - 1 ; i <= node.x + 1 ; i=i+1)
			for(int j = node.y - 1 ; j <= node.y + 1 ; j=j+1)
			{	
			// i_k = i;j_k = j;
			//cout<<"("<<i<<","<<j<<") node ("<<node.x<<","<<node.y<<")"<<endl;;
			/*if(Grid[i*cols + j].S==Target)
					{
						TargetReached = true;
						Grid[i*cols + j].R = R;
						tarI=i;tarJ=j;
						cout<<"Target Reached at ("<<tarI<<","<<tarJ<<")"<<endl;
						break;
					}*/
			//if(i>rows && j>cols |TargetReached) {out=true; break;}
			if( (i >= 0) && (i < rows ) && (j >= 0) && (j < cols ) && (abs(i-node.x)*abs(j-node.y)==0) )
			{
						
				//cout<<"("<<i<<","<<j<<") before "<<Grid[i*cols + j].S<<endl;
				if(Grid[i*cols + j].S==Target && (i<rows) && (j<cols))
					{
						TargetReached = true;
						Grid[i*cols + j].R = R;
						tarI=i;tarJ=j;
						cout<<"Target Reached at ("<<tarI<<","<<tarJ<<")"<<(i<rows)<<" "<<(j<cols)<<endl;
						break;
					}
				if( (Grid[i*cols + j].S==Idel || Grid[i*cols + j].S==Label) && !Grid[i*cols + j].NS && Grid[i*cols + j].S!=Block  && Grid[i*cols + j].S!=Target && !TargetReached)
				{
					//cout<<"("<<i<<","<<j<<") after"<<Grid[i*cols + j].S<<endl;
					if(Grid[i*cols + j].S==Target)
					{
						TargetReached = true;
						Grid[i*cols + j].R = R;
						tarI=i;tarJ=j;
						cout<<tarI<<","<<tarJ<<endl;
						break;
					}
					
					
					
					if(!Grid[i*cols + j].NS){
						Grid[i*cols + j].R = R;
						Grid[i*cols + j].S = Label;
						if((i-node.x)==-1 && (j-node.y)==0) Grid[i*cols + j].flag[3] = true;
						if((i-node.x)==0 && (j-node.y)==-1) Grid[i*cols + j].flag[2] = true;
						if((i-node.x)==0 && (j-node.y)==1) Grid[i*cols + j].flag[1] = true;
						if((i-node.x)==1 && (j-node.y)==0) Grid[i*cols + j].flag[0] = true;
						ui.update(Point(i,j),Grid[i*cols + j].flag,R,"Wave");
						cout<<Grid[i*cols + j].NS<<endl;
						L.push_back(Point(i,j));
					}
					if(i==node.x && j==node.y) Grid[i*cols + j].NS = true;//cout<<"("<<i<<","<<j<<")"<<"herree "<<Grid[i*cols + j].NS<<endl;}
					update=true;
					
				}
				
				
				}
			}
			if(update)
			{
			
			for(int ii=0;ii<rows;ii++)
			{
			for(int jj=0;jj<cols;jj++)
			{
				//cout<<Grid[ii*cols + jj].S<<" ";
				if(Grid[ii*cols	 + jj].S==Label){
				//	ui.update(Point(ii,jj));
				}
				
			}
				//cout<<endl;
			}
			//cout<<endl;
			}
		
		
		}
		R = R+1;
		//if(R==6) while(1){}
		cout<<endl;
		label.clear();
		label = L;
		cout<<L.size()<<endl;
		//cout<<Mat(L)<<endl;
	}
	
//	cout<<tarI<<","<<tarJ<<endl;
		vector<Point> PointPath;
	if(TargetReached)
	{	
		
		cout<<"Back Trace "<<endl;
		cout<<"Target Reached at Radius "<<Grid[tarI*cols + tarJ].R<<endl; ;
		int Radius = Grid[tarI*cols + tarJ].R ;
		bool SourceReached=false;Point node = Point(tarI,tarJ);
		bool flagN=false,flagE=false,flagW=false,flagS=false;
		while( !SourceReached )
		{
			
			vector<Point>p;
			for(int i=node.x-1;i<=node.x+1;i++)
			for(int j=node.y-1;j<=node.y+1;j++)
			{
				//cout<<!(flagN |flagE | flagW | flagS)&&(abs(i)*abs(j)==0)<<endl;
				if(i >= 0 && i < rows && j>=0 && j < cols) 
				{
				cout<<"("<<node.x<<","<<node.y<<")"<<"("<<i<<","<<j<<")"<<" "<<Grid[i*cols + j].R<<endl;
				if(!(flagN |flagE | flagW | flagS) && (abs(i-node.x)*abs(j-node.y)==0))
				{
					cout<<"("<<i<<","<<j<<") before "<<Grid[i*cols + j].S<<" "<<Grid[i*cols + j].R<<endl;
				
					if(Grid[i*cols + j].R <= Radius && Grid[i*cols + j].S != Block && Grid[i*cols + j].S != Idel && Grid[i*cols + j].S == Label && !SourceReached )
					{					
						
						cout<<"here"<<endl;
						if(i-node.x==-1 & j-node.y==0)
						{
							flagN = true;
							PointPath.push_back(Point(i,j));			
							//ui.update(Point(i,j),R,"TraceBack");
							Grid[i*cols + j].S = Trace;
							cout<<"N"<<endl;
							Radius = Grid[node.x*cols + node.y].R;
							node.x = i;
							node.y = j;
							
							break;
						}
						if(i-node.x==0 & j-node.y==-1)
						{
							flagW = true;
							cout<<"W"<<endl;
							PointPath.push_back(Point(i,j));			
							//ui.update(Point(i,j),R,"TraceBack");
							Grid[i*cols + j].S = Trace;
							Radius = Grid[node.x*cols + node.y].R;
							node.x = i;
							node.y = j;
								break;
						}
						if(i-node.x==0 & j-node.y==1)
						{
							flagE = true;
							cout<<"E"<<endl;
							PointPath.push_back(Point(i,j));			
							//ui.update(Point(i,j),R,"TraceBack");
							Grid[i*cols + j].S = Trace;
							Radius = Grid[node.x*cols + node.y].R;
							node.x = i;
							node.y = j;
								break;
						}
						if(i-node.x==1 & j-node.y==0)
						{
							flagS = true;
							cout<<"S"<<endl;
							PointPath.push_back(Point(i,j));			
							//ui.update(Point(i,j),R,"TraceBack");
							Grid[i*cols + j].S = Trace;
							Radius = Grid[node.x*cols + node.y].R;
							node.x = i;
							node.y = j;
								break;
						}
					}
					
					
					
				if(Grid[i*cols + j].S == Source) 
					{
						
						cout<<" SourceReached "<<endl;
						SourceReached = true;
						break;
					}
				
				}
				if(flagN |flagE | flagW | flagS) break;
					
			}
			}
				//cout<<"here"<<endl;
				//cout<<"here"<<endl;
				/*vector<int> minR;
				if(flagN)
					minR.push_back(Grid[(node.x-1)*cols + node.y].R);
				else	
					minR.push_back(1000);
				
				if(flagW)
					minR.push_back(Grid[(node.x)*cols + node.y+1].R);
				else	
					minR.push_back(1000);
				
				if(flagE)
					minR.push_back(Grid[(node.x)*cols + node.y-1].R);
				else	
					minR.push_back(1000);	
				
				if(flagS)
					minR.push_back(Grid[(node.x+1)*cols + node.y].R);
				else	
					minR.push_back(1000);	
				int idx = distance(minR.begin(), min_element(minR.begin(), minR.end()));
				
				int x[]={-1,0,0,1};
				int y[]={0,1,-1,0};
				if(minR.size()>1)
				{
				node.x = node.x+x[idx];
				node.y = node.y+y[idx];
				}
				//else node.x = 
				cout<<Mat(minR)<<endl;
				cout<<"nee ("<<node.x<<","<<node.y<<")"<<endl;
				* */
				flagN=false;flagE=false;flagW=false;flagS=false;
			
			
		}
	}
	vector<Point>PP;
	PP.push_back(source);
	PP.push_back(target);
	PP.push_back(Point(3,3));
	PP.push_back(Point(4,4));
	PP.push_back(Point(0,5));
	PP.push_back(Point(1,5));
	
	ui.ShowJustPath(PointPath);
		
		
		
	

	
	return 0;
}

