
#include "../inc/IO.hpp"

int getRow(const string filename)
{	
	ifstream infile;
	infile.open(filename);
	if(!infile.is_open()){
        cout << "Could not open the file " << filename << endl;
        cout << "The program is terminated." << endl;
        exit(EXIT_FAILURE);
    }
    int rowcnt = 0;
    string c;
	getline(infile, c, '\n');
	while (infile.good())
	{
		rowcnt++;
		getline(infile, c, '\n');
	}
	
	cout << rowcnt << endl;
		
	if(infile.eof()) cout << "The end of file " << filename << " is reached" << endl; 
	else if(infile.fail()) cout << "failure" << endl;
		
    infile.close();
	return rowcnt; 
}

int getCol(const string filename) 
{	
	ifstream infile;
	infile.open(filename);
    if(!infile.is_open()){
        cout << "Could not open the file " << filename << endl;
        cout << "The program is terminated." << endl;
        exit(EXIT_FAILURE);
    }
    int colcnt=0;
	char c;
    c = infile.get();
	while(c != '\n' && c != '\r' && infile.good()){
		if(c == ' ') colcnt++;
		c = infile.get();
	}
	colcnt++;
	cout << colcnt << endl;

    if(infile.eof()) cout << "The end of file " << filename << " is reached" << endl; 
	else if(infile.fail()) cout << "failure" << endl;

	infile.close();
	return colcnt;
}

void inputdo(double *matrix, int row, int col, const string filename)
{
	ifstream infile;
	infile.open(filename);
	while(infile.good()){
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				infile >> *(matrix + j + i * row);
			}
		}
	}
	infile.close();
}

void outputdo(double *matrix,int row,int col,const string filename)
{
	ofstream outfile;
	outfile.open(filename);
	for(int i=0;i<row;i++)
	{
	 	for(int j=0;j<col;j++)
	 	{
	 		outfile << fixed << setprecision(6) << *(matrix + i*row + j) << '\t';
		}
		outfile<<endl;
	}
	outfile.close();
	cout << "The outcome is created!" << endl;
}

void inputfl(float *matrix, int row, int col, const string filename)
{
    ifstream infile;
    infile.open(filename);
    while(infile.good()){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                infile >> *(matrix + j + i * row);
            }
        }
    }
    infile.close();
}

void outputfl(float *matrix,int row,int col,const string filename)
{
    ofstream outfile;
    outfile.open(filename);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            outfile << fixed << setprecision(6) << *(matrix + i*row + j) << '\t';
        }
        outfile<<endl;
    }
    outfile.close();
	cout << "The outcome is created!" << endl;
}
