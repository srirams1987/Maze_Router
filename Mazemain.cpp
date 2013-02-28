

#include "Maze.h"


int main(int argc, char *argv[] )
{
	/*if(argc < 2)
	{
		cout<<"Usage ./maze <parameters.txt> ";
		}
		* */
	
	
	
	int rows = 7;
	int cols = 7;
	vector<Point>P;
	Point target= Point(6,2)	;
	Point source= Point(2,5)	;

	P.push_back(source);
	P.push_back(target);
	P.push_back(Point(3,3));
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
				cout<<i<<","<<j<<" "<<Grid[i*cols + j].S<<" ";
				cout<<Grid[i*cols + j].flag[0]<<" "<<Grid[i*cols + j].flag[1]<<" "<<Grid[i*cols + j].flag[2]<<" "<<Grid[i*cols + j].flag[3]<<endl;
							
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
		//cout<<"Radius "<<R<<" T "<<TargetReached<<endl;
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
			
			if( (i >= 0) && (i < rows ) && (j >= 0) && (j < cols ) && (abs(i-node.x)*abs(j-node.y)==0) )
			{
						
				
				if(Grid[i*cols + j].S==Target && (i<rows) && (j<cols))
					{
						TargetReached = true;
						Grid[i*cols + j].R = R;
						tarI=i;tarJ=j;
						cout<<Grid[i*cols + j].flag[0]<<" "<<Grid[i*cols + j].flag[1]<<" "<<Grid[i*cols + j].flag[2]<<" "<<Grid[i*cols + j].flag[3]<<endl;
						if((i-node.x)==-1 && (j-node.y)==0) Grid[i*cols + j].flag[3] = true;
						if((i-node.x)==0 && (j-node.y)==-1) Grid[i*cols + j].flag[2] = true;
						if((i-node.x)==0 && (j-node.y)==1) Grid[i*cols + j].flag[1] = true;
						if((i-node.x)==1 && (j-node.y)==0) Grid[i*cols + j].flag[0] = true;
						cout<<"Target Reached at ("<<tarI<<","<<tarJ<<")"<<(i<rows)<<" "<<(j<cols)<<endl;
						break;
					}
				if( (Grid[i*cols + j].S==Idel || Grid[i*cols + j].S==Label) && !Grid[i*cols + j].NS && Grid[i*cols + j].S!=Block  && Grid[i*cols + j].S!=Target && !TargetReached)
				{
				
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
						
						if((Grid[i*cols + j]).checkLable())
							L.push_back(Point(i,j));
					}
					if(i==node.x && j==node.y) Grid[i*cols + j].NS = true;
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
		
		if(TargetReached) break;
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
	if(!TargetReached)
	{
		cout<<"Target not Found "<<endl;
		return 0;

	}
		
		cout<<"Back Trace "<<endl;
		cout<<"Target Reached at Radius "<<Grid[tarI*cols + tarJ].R<<endl; ;
		cout<<Grid[tarI*cols + tarJ].flag[0]<<" "<<Grid[tarI*cols + tarJ].flag[1]<<" "<<Grid[tarI*cols + tarJ].flag[2]<<" "<<Grid[tarI*cols + tarJ].flag[3]<<endl;
		int Radius = Grid[tarI*cols + tarJ].R ;
		bool SourceReached=false;
		Point node = Point(tarI,tarJ);
		vector<Point> path;
		while( !SourceReached )
		{
			
			if(Grid[node.x*cols + node.y].flag[0])
				node = node + Point(-1,0);
			else if(Grid[node.x*cols + node.y].flag[1])
				node = node + Point(0,-1);
			else if(Grid[node.x*cols + node.y].flag[2])
					node = node + Point(0,1);
			else if(Grid[node.x*cols + node.y].flag[3])
					node = node + Point(1,0);

			if(Grid[node.x*cols + node.y].S == Source)
				 SourceReached = true;

			path.push_back(node);
			cout<<Mat(path)<<endl;


				}


		ui.ShowJustPath(path);
			
	
	
	return 0;
}

