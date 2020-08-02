#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<mem.h>
/* Description of the input function:   
Each of the subsequent lines of the file describes one cube – you have the same
number of lines as the second line of your file. Each of these lines also has a set
of numbers: the first number on the line says how many variables are not don’t
cares in this cube. If this number is, e.g., 5, then the next 5 numbers on the line
specify the true or complemented form of each variable in this cube. We use a
simple convention: if variable xk appears in true form, then put integer “k” on
the line; if variable xk appears in complement form (xk’) then put integer “-k”
on the line. The file will always order these variables in increasing index order.
So, if your cube has (x3x5x9’ ), the line should say “3 3 5 -9” and not
some other order, e.g., “3 -9 3 5”. Spaces on the line do not matter.*/
//------
//you should provide your boolean func."the input" represented in aPCNCube List file just like the "part5.pcn" file or just in a text file, and 
//put the name of the file in the line number 309.
//then, put the name of the output file "the complemnt of your boolean func." in the line number 254 and 289, and 
//finally, put the name of the output file "the cube list of your boolean func."in the line number 404
//------ 

int NumOfSlots=0;int NumOfCubes=0,NumTheDontCareVars=0; // global variables

int find_most_binate_var (int list1 [NumOfCubes][NumOfSlots],int*b)
{printf("------------\n");
printf("Data about The most binate value:\n");
printf("======================================\n");
int Namevar;
int h=0,g,i,k;int appear[NumOfSlots];
int TureForm[NumOfSlots],FalseForm[NumOfSlots],binate[NumOfSlots];
int min_binate,IndexOfMax ,IndexOfMin,max_appear;
bool equalybinate =0,equalappear=0;
int lessIndexunate[NumOfSlots];
bool nobinate=0;

for (i=0;i<NumOfSlots;++i)
	{appear[i]=0;TureForm[i]=0;FalseForm[i]=0; binate[i]=0;
	for(k=0;k<NumOfCubes;++k)
		{if (list1[k][i]==1) {++appear[i];++TureForm[i];}
		else if (list1[k][i]==0) {++appear[i];++FalseForm[i];}}	}
//obtain the binate state of all vars
for (i=0;i<NumOfSlots;++i) binate[i]=abs((TureForm[i]-FalseForm[i]));

//find max value in the appear array
max_appear=appear[0];
IndexOfMax=0;
for (i=1;i<NumOfSlots;++i)
	{if (appear[i]>max_appear)
	{max_appear=appear[i];
	IndexOfMax=i;}}
	//remove it !!!!!!!!!
	for (i=0;i<NumOfSlots;++i)
	printf("binate[%d]=%d\n",i+1,binate[i]);
	printf("------\n");
	for (i=0;i<NumOfSlots;++i)
	printf("appear[%d]=%d\n",i+1,appear[i]);
	printf("------\n");	
	//stop removing 
//know how many element equal the max appear value 
k=0;
for (i=0;i<NumOfSlots;++i)
{if (appear[i]==max_appear&&!(IndexOfMax==i)){equalappear=1; ++k;}}
//check if there is no a binate var
for (i=0;i<NumOfSlots;++i)
	{if(TureForm[i]==0||FalseForm[i]==0)
	 {lessIndexunate[h]=i;
	 	++h;}}
if (h==NumOfSlots)	{nobinate=1; *b=0;Namevar=IndexOfMax+1; return Namevar;}
if (equalappear&&!(nobinate))
{//obtain all indexes of the elements that equal to the max value in the appear array and save they in "lessIndexappear"
equalappear=0;
++k;
int lessIndexappear[k];
int count1=0;
for (i=0;i<NumOfSlots;++i)
	{if (appear[i]==max_appear)
	{lessIndexappear[count1]=i;
	++count1;}}	
	//remove!!!
		for (i=0;i<k;++i)
	printf("lessIndexappear[%d]=%d\n",i,lessIndexappear[i]);printf("-------\n");
//obtain the binate value of all elements that their index in "lessIndexappear" array
int BinateOfMostAppear[k];
for (i=0;i<k;++i)	BinateOfMostAppear[i]=binate[lessIndexappear[i]];
	for (i=0;i<k;++i)//remove !!!
	printf("BinateOfMostAppear[%d]=%d\n",i,BinateOfMostAppear[i]);printf("------\n");
//obtain the min value in the "BinateOfMostAppear" array
min_binate=BinateOfMostAppear[0];
IndexOfMin=0;
for (i=1;i<k;++i)
{if (BinateOfMostAppear[i]<min_binate)
	{min_binate=BinateOfMostAppear[i];
	IndexOfMin=i;}} printf("min_binate=%d\tIndexOfMin=%d\n",min_binate  ,IndexOfMin);
//know how many element equal the min BinateOfMostAppear value 
int count=0;
for (i=0;i<k;++i)
{ if (BinateOfMostAppear[i]==min_binate&&!(IndexOfMin==i))	{equalybinate=1;	++count;}}
if (equalybinate)
{//return the index of the first element that equal the min value in the binate and appear values  
equalybinate=0;
for (i=0;i<NumOfSlots;++i)
{if (binate[i]==BinateOfMostAppear[0]){ Namevar=i+1;break;}}
return Namevar;}
else
{for (i=0;i<NumOfSlots;++i)
{if (binate[i]==min_binate){ Namevar=i+1;;break;}}
return Namevar;}

}
else {Namevar=IndexOfMax+1;return  Namevar;}
}
//a func return num of rows of the positiveCofactor cube list
int NumOfPosExistingRows(int list3[NumOfCubes][NumOfSlots],int var)
{printf("-------------------|\n");
printf("Data about The PosCofactor of Var[%d]:\n",var);
printf("======================================\n");
int k=0;
int NumFalseInTheCertainSlot=0;
	var=var-1;
	for(k=0;k<NumOfCubes;++k)
		{if(list3[k][var]==0) ++NumFalseInTheCertainSlot;}
	int NumOfRows=NumOfCubes-NumFalseInTheCertainSlot;//number of the rows in the new array -->"Cofactor"array in "Cofactor" func.
		printf("number of the columns in the new /PosCofactor/ array=%d\n",NumOfRows);
	return	NumOfRows;
}
//Cofactor func declaration
void Cofactor (int list3[NumOfCubes][NumOfSlots],int var,int NumOfRows,char state ,int Cofactor[][NumOfSlots])
{	int h,g,i,k=0;														//state must be 'p' or 'n' 
	var=var-1;															// note that p & n are small characters
	Cofactor[NumOfRows][NumOfSlots];
	//initializate the CubeList array(assuming all vars don't care)
	 for (h=0;h<NumOfRows;++h)
	{for (g=0;g<NumOfSlots;++g)
	 Cofactor[h][g]=2;}
//Obtain all indexes of all rows that will be existed in the new array
int IndexofExistingRow[NumOfRows];
	int count=0;
	if (state=='p')
	{for (k=0;k<NumOfCubes;++k)
		
		{if (list3[k][var]==1||list3[k][var]==2) 
			{IndexofExistingRow[count]=k;
			++count;}}
	for (i=0;i<count;++i)		
		printf ("IndexofPosExistingRow[%d]=%d\n",i,IndexofExistingRow[i]);}
		else
		{for (k=0;k<NumOfCubes;++k)
		{if (list3[k][var]==0||list3[k][var]==2) 
			{IndexofExistingRow[count]=k;
			++count;}}
				for (i=0;i<count;++i)		
		printf ("IndexofNegExistingRow[%d]=%d\n",i,IndexofExistingRow[i]);}
		//set the other slots in the new array
	for (i=0;i<NumOfSlots;++i)
	{if (var!=i)
		{for (k=0;k<NumOfRows;++k)
		Cofactor[k][i]=list3[IndexofExistingRow[k]][i];}}
	//printing the new array	
	for	(k=0;k<NumOfRows;++k)
	{for (i=0;i<NumOfSlots;++i)printf(" %d",Cofactor[k][i]);
	printf ("\n");	}	
printf("--------------|\n");
}
//a func return num of rows of the NegitiveCofactor cube list
int NumOfNegExistingRows(int list3[NumOfCubes][NumOfSlots],int var)
{printf("-------------------|\n");
printf("Data about The NegCofactor of Var[%d]:\n",var);
printf("======================================\n");
int k=0;
var=var-1;
int NumTrueInTheCertainSlot=0;
	for(k=0;k<NumOfCubes;++k)
		{if(list3[k][var]==1) ++NumTrueInTheCertainSlot;}
	int NumOfRows=NumOfCubes-NumTrueInTheCertainSlot;//number of the rows in the new array -->"PosCofactor"array
		printf("number of the columns in the new /NegCofactor/ array=%d\n",NumOfRows);
	return	NumOfRows;
}
//a func. anded a variable with its cofactor 
void ANDVC(int list3[][NumOfSlots],int NumOfRows,int var,int state,int result[][NumOfSlots] )
{var=var-1;	//list3 is the cofactor//NumOfRows of the cofactor//"var"-->name of the var. and"state"-->is true of false 
int i , k ;																			    	//1 OR 0
//copy the list3 array in the result array
for (i=0;i<NumOfSlots;++i)
{for (k=0;k<NumOfRows;++k)
{result[k][i]=list3[k][i];}}
//do the AND operation based on the state of the var.
if (state==1 )
{for (k=0;k<NumOfRows;++k)
{if (list3[k][var]==2)result[k][var]=1;
else {printf("Error: there is a True form or a False form, so the AND operation stops!!\n ");break;}}}
else
{for (k=0;k<NumOfRows;++k)
{if (list3[k][var]==2)result[k][var]=0;
else {printf("Error: there is a True form or a False form, so the AND operation stops!!\n ");break;}}}
}
//func. concatenates 2 cube lists --> an OR operation 
void ORCC (int list1[][NumOfSlots],int NumRows1,int list2[][NumOfSlots],int NumRows2 ,int result [][NumOfSlots])
{int i,k,h;
int TotalRows=NumRows1+NumRows2;
result [TotalRows][NumOfSlots];
for (i=0;i<NumOfSlots;++i)
{//copy the first array in the result array 
for (k=0;k<NumRows1;++k)
result[k][i]=list1[k][i];
// copy the second array 
for (h=0;h<NumRows2;++h)
{result[k][i]=list2[h][i];++k;}
}
//print the result array 
	printf("======================================\n");
	printf("The Complement Function as a cube list:\n");
	printf("======================================\n");
	for(i=0;i<TotalRows;++i)
	{for (k=0;k<NumOfSlots;++k) printf(" %d",result[i][k]);
	printf("\n");}
	printf("======================================\n");
}
// URP Complement func
bool complement (int list[NumOfCubes][NumOfSlots])
{int h,g,k=0,i;
bool simply=0;
bool DeMorgan=1,complement=0; 
char talk2[]="-----------------------------------\n";   
//check if the cube list is one and all the vars don't care
	if (NumOfCubes==1)
	{for(i=0;i<NumOfSlots;++i)
		{if (list[0][i]==2) NumTheDontCareVars=NumTheDontCareVars+1;}
		if (k==NumOfSlots)	
		{DeMorgan=0;	
		simply=1;complement=0;
		return complement;}}	
	//has no cubes in it, then this represents the Boolean equation “0”
	if (NumOfCubes==0)	{simply=1; complement=1;
						return complement;}
	//Apply DeMorgan's law on an one cube or a product term
	if (DeMorgan==1 && NumOfCubes==1 )
	{ int DeMorganMatrix[NumOfSlots-NumTheDontCareVars][NumOfSlots];
	 //initializate the CubeList array(assuming all vars don't care)
	 for (h=0;h<(NumOfSlots-NumTheDontCareVars);++h)
	{for (g=0;g<NumOfSlots;++g)
	 DeMorganMatrix[h][g]=2;}
	 //obtain the DeMorgan's cube list
		for(i=0;i<NumOfSlots;++i)
		{ if (list[0][i]==1){printf("i=%d...k=%d\n",i,k);DeMorganMatrix[k][i]=0;++k;}
		 else if (list[0][i]==0){printf("i=%d...k=%d for list's element ='0\n",i,k);DeMorganMatrix[k][i]=1;++k;}}  
		simply=0;
		k=0;
//print the result of applying the demorgan's law in a existing text file, 
//note that you must declare that file and save it beside the application itself
//put the name of the saving file at two places (follow the comments).
FILE* write_file2=fopen("complementOfpart5.txt","w");												//here is the first place.(the complement of the boolean func.)
char talk3[]="Applying DeMorgan's law: ";
fputs (talk3,write_file2);fputc('\n',write_file2);
fputs (talk2,write_file2);
fputc('\n',write_file2);
for (i=0;i<(NumOfSlots-NumTheDontCareVars);++i)
	{for (k=0;k<NumOfSlots;++k)
	fprintf(write_file2," %d",DeMorganMatrix[i][k]);
	fputc('\n',write_file2);}
	fputs (talk2,write_file2);
}
		
	//if the func not simple then ...
int binateVar=0,binateState=1;
binateVar=find_most_binate_var(list,&binateState);//&binateState meaning, pass the address of the var. "binateState" 
printf("binateState=%d\tbinateVar=%d\n", binateState ,binateVar);
//Pos. cofactor 
    int PosNum= NumOfPosExistingRows(list,binateVar);
	int PosCofactor[PosNum][NumOfSlots];
	Cofactor(list,binateVar,PosNum,'p',PosCofactor);
//	Neg. cofactor
	 int NegNum= NumOfNegExistingRows(list,binateVar);
		int NegCofactor[NegNum][NumOfSlots];
	Cofactor(list,binateVar,NegNum,'n',NegCofactor);
	
	int TheFinalResult[(PosNum+NegNum)][NumOfSlots];
	ORCC(PosCofactor,PosNum,NegCofactor,NegNum,TheFinalResult);
// covert the final result into the input type
int rows=PosNum+NegNum;
int numOfTheDontCareVarsInEveryRow[rows];
for(i=0;i<rows;++i)
{numOfTheDontCareVarsInEveryRow[i]=0;
for(k=0;k<NumOfSlots;++k)
{if (TheFinalResult[i][k]!=2)numOfTheDontCareVarsInEveryRow[i]=numOfTheDontCareVarsInEveryRow[i]+1;}}
//print the final result in the saving file.
FILE* txt=fopen("complementOfpart5.txt","w");																//here is the second place.(the complement of the boolean func.)
char talk4[]="the complement: ";
fputs(talk4,txt);
fputc('\n',txt);
fprintf(txt,"%d",NumOfSlots);fputc('\n',txt);
fprintf(txt,"%d",rows);fputc('\n',txt);

for(i=0;i<rows;++i)
{fprintf(txt,"%d",numOfTheDontCareVarsInEveryRow[i]);
for(k=0;k<NumOfSlots;++k)
{if (TheFinalResult[i][k]==1) fprintf(txt," %d",(k+1));
else if (TheFinalResult[i][k]==0) fprintf(txt," -%d",(k+1));}
fputc('\n',txt);
}
fputc('\n',txt);
fclose(txt);
}
		

//========================================================================================================================


int main ()
{FILE *CubeListFile = fopen("part5.pcn","r");    											/// put the input file here "the boolean function".
int j=0,k=0,i=0;
int h,g;
//make sure there is no an error in the reading operation
if (CubeListFile==NULL)
{printf("the file doesn't be read!\n");
return 0; }
else {printf("the reading operation is done!\n");
printf("---------------------------------\n");}
// making an 2D array that represents a Cube List of the func.
char ch[3000];
char c[2];
char c1[6];
char c2[2]="  ";
//get the NumOfSlots
fgets(ch,1024,CubeListFile); // read a whole line from the file
printf ("The original Number Of Slots="); puts(ch);
NumOfSlots=atoi(ch);
printf("the variable ..NumOfSlots.. =%d\n",NumOfSlots);
printf("---------------------------------\n");
//get the NumOfCubes 
fgets(ch,1024,CubeListFile);
NumOfCubes=atoi(ch);
printf ("The original Number Of cubes="); puts(ch);
printf("the variable...NumOfCubes..=%d\n",NumOfCubes );
printf("====================================================\n");
// collect the don't care variables in 3 stages(check the complement status,collect the chars that have the name of the var. , convert they to a int type and save they in "var" variable
//and full stage   
int NumOfNotDontCareVars;
int var,LenOfVarName=0;
int row=0;
bool comp,full,collect=0;
int CubeList[NumOfCubes][NumOfSlots];
for (h=0;h<NumOfCubes;++h)//initializate the CubeList array(assuming all vars don't care)
{for (g=0;g<NumOfSlots;++g)
	CubeList[h][g]=2;}
//obtain the cube list of the given func.
//where "2" represent a don't care case , "1" represent a true form of the var. and "0" represent a camplement form of the var.	
while (!feof(CubeListFile))
{
fgets(ch,3000,CubeListFile);
for(i=0;i<=1;i=i+1)	c[i]=ch[i];
NumOfNotDontCareVars=atoi(c);
for (j=0;j<NumOfNotDontCareVars;j++)
{//check the complement status
	if(ch[i]=='-')
			{
			collect=1;
			comp=1;	
			++i;
			}
		else
			{
			collect=1;
			comp=0;
			}
	//collect the chars
	if (collect==1)
		{   while (!(isspace(ch[i])))
				{c1[LenOfVarName]=ch[i];
				++LenOfVarName;
	        	++i;
				if (ch[i]=='\n')break; }
			if (LenOfVarName==1)
				{LenOfVarName=0;
				c[0]=c1[0];
				c[1]=c2[0];
				var=atoi(c);}
			else
				{LenOfVarName=0;
				var=atoi(c1);}
			full=1;
			collect=0; }
	//full stage
		
	if (full==1)//the first part
		{if (comp==1) 
		CubeList[row][var-1]=0; 
		else
		CubeList[row][var-1]=1;
		full =0;}
	++i;
	if (ch[i]=='\n') break;	
	if ((isspace(ch[i])))	++i;
					
}

++row;
if (row>(NumOfCubes-1))  break;
}
// printing the obtained cube list to an user
FILE* write_file=fopen("CubeListOfpart5.txt","w");											///put the saving file here (the cube list of the boolean function)
char talk1[]="note that: '2' represent a don't care case,'1' represent a true form of the var. and '0' represent a camplement form of the var.";
char talk2[]="-----------------------------------\n";
fputs (talk1,write_file);fputc('\n',write_file);
fputs (talk2,write_file);
fputc('\n',write_file);
for (i=0;i<NumOfCubes;++i)
	{for (k=0;k<NumOfSlots;++k)
	fprintf(write_file," %d",CubeList[i][k]);
	fputc('\n',write_file);}
	fputs (talk2,write_file);
//printing the complement of the func in a existing file
int mat[NumOfNotDontCareVars][NumOfSlots];
complement(CubeList);//the complement func. obtains the comlement value of the given boolean function and print the result at a existing file 

}
