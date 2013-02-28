


#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



typedef enum state{ Source, Block, Label, Target, Idel,Trace};

class PE
{
	public:
		PE()
		{
			S = Idel;
			R =0;
			TraceBack = Point(0,0);
			flag[0]=false;flag[1]=false;flag[2]=false;flag[3]=false;
			NS = false;
		}
		~PE()
		{
			}	
		state S;
		int R;
		bool NS;
		Point TraceBack;
		bool flag[4];
		
		
		bool checkLable()
		{
			return flag[0]||flag[1]||flag[2]||flag[3];
			
		}	
};



class UI{
	private:
	
	int rows,cols;
	vector<Mat> PE_cells;
	Mat Img;
	vector<Point> Init;
	
	public:
	
	UI(int r,int c);
	~UI();
	void DispInit(vector<Point> Src);
	void update(Point P,bool flag[4],int R,string Stage);
	void ShowJustPath(vector<Point> Src);
	
	
	};


