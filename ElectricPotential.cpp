#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>


using std::cout;
using std::cin;
using std::endl;
using std::abs;
using std::vector;
using std::ifstream;

vector<vector<double> > potential;
int Nbox;
// for a vector of double vectors to find potential
double getV (int i , int j )
{
	return potential.at( i + Nbox ).at( j + Nbox );
}
void setV(int i , int j , double value )
{
	potential.at( i + Nbox ).at( j + Nbox ) = value ;
}

// Electric Field of the X-direction helper function
vector<vector<double> > EatX;
double getEx (int i , int j )
{
	return EatX.at( i + Nbox ).at( j + Nbox );
}
void setEx(int i , int j , double value )
{
	EatX.at( i + Nbox ).at( j + Nbox ) = value ;
}
//Electric Field of the Y-direction helper function
vector<vector<double> > EatY;
double getEy (int i , int j )
{
	return EatY.at( i + Nbox ).at( j + Nbox );
}
void setEy(int i , int j , double value )
{
	EatY.at( i + Nbox ).at( j + Nbox ) = value ;
}

//potential.resize(2*Nbox+1, vector<double>(2*Nbox+1));

bool ontheplates(int i ,int j,int NLplate,int Nplate)
{
	if ((i <= NLplate && i >= -NLplate) && (j == Nplate || j == -Nplate))
		return true;
	else 
		return false;
}
	
int main(int argc, char** argv)
{
int Lbox;
int L; 
int Nplate;

ifstream params;
	params.open("params.txt");
	while(!params.eof())
	{
	params >> L;
	params >> Lbox;
	params >> Nplate;
	}
	params.close();


double delta = 1.0 / Nplate;
double NLplate = L * Nplate;
Nbox = Lbox * Nplate;
int stepboxes = 2 * Nbox + 1;
potential.resize(2*Nbox+1,vector<double>(2*Nbox+1));
EatX.resize(2*Nbox+1,vector<double>(2*Nbox+1));
EatY.resize(2*Nbox+1,vector<double>(2*Nbox+1));

//Set Potentail at Upper Plates (1) and Lower Plates (-1)
for (int i = -NLplate; i <= NLplate; i++)
    {
        setV(i,Nplate,1.0);
        setV(i,-Nplate,-1.0);
	}

/* int iter = 0;
// Laplace solution to potential of a 2D vector by averaging 4 neighboring sites. Needs to exclude ontheplate
while (iter < 1000)
{
	for (int i = -Nbox+1; i <= Nbox-1; i++)
		for (int j= -Nbox+1; j <= Nbox-1; j++)
			if(!ontheplates(i,j,NLplate,Nplate))
			setV(i,j, 1.0/4*(getV(i+1,j) + getV(i-1,j)+getV(i,j+1)+getV(i,j-1)));
	
	// Relaxation method using bitwise operators in for loop	
	// Percentage difference to check the differences between two set of values to determine
	// if our potential is within low tolerance using relaxation method.
	
	cout << "Iterations #:" << iter << endl;
	iter++;
} */

double toldiff = 1.0;
double new_trace = -1.0;
double old_trace;
double tolerance = .001;
int iter = 0;
while (toldiff > tolerance)
{
	old_trace = new_trace;
	for (int i = -Nbox+1; i <= Nbox-1; i++)
		for (int j= -Nbox+1; j <= Nbox-1; j++)
			if(!ontheplates(i,j,NLplate,Nplate))
			setV(i,j, 1.0/4*(getV(i+1,j) + getV(i-1,j)+getV(i,j+1)+getV(i,j-1)));
		
	// Relaxation method using bitwise operators in for loop	
	// Percentage difference to check the differences between two set of values to determine
	// if our potential is within low tolerance using relaxation method.
	
	for (int i = -Nbox+1; i <= Nbox-1; i++)
		new_trace += pow(getV(i,i),2);
		toldiff = std::abs(1.0*(new_trace-old_trace)/old_trace);
	
	
	cout << "Iterations #:" << iter << " " << toldiff << endl;
	iter++;
}
// Making a potential text file in the format of x y V(x,y)
std::ofstream sol("potential.txt");
    if(sol.is_open())
        cout << "sol stream opened successfully." << endl;
    else
    {
        cout << "sol stream failed to open!" << endl;
        return EXIT_FAILURE;
    }
    for(int i = -Nbox; i <= Nbox; i++)
        for(int j = -Nbox; j <= Nbox; j++)
            sol << i * 1.0 * delta << " " << j * 1.0 * delta << " " << getV(i,j) << endl;
	sol.close();
// Now iterating the Electric field of x
std::ofstream electricfield("electricfield.txt");
	if(electricfield.is_open())
		 cout << "electricfield stream opened successfully." << endl;
    else
    {
        cout << "electricfield stream failed to open!" << endl;
        return EXIT_FAILURE;
    }
	for(int i = -Nbox + 1; i <= Nbox - 1; i++)
        for(int j = -Nbox + 1; j <= Nbox - 1; j++)
        {
        setEx( i , j , (getV(i+1,j) - getV(i-1,j) ) * -1.0 / ( 2 * delta ));   
        }
	for(int i = -Nbox + 1; i <= Nbox - 1; i++)
        for(int j = -Nbox + 1; j <= Nbox - 1; j++)
		{
        setEy( i , j , (getV(i,j+1) - getV(i,j-1) ) *-1.0 / ( 2 * delta ));
		}
	for(int i = -Nbox; i <= Nbox; i++)
		for(int j = -Nbox; j <= Nbox; j++)
			electricfield << i * 1.0 * delta << " " << j * 1.0 * delta << " " << getEx(i,j) << " " << getEy(i,j) << endl;

	electricfield.close();



}

// Trace = diagonal of a matrix
// central derivative for finding Ex and Ey
// One python script per plot

//params 
//2
//5
//4