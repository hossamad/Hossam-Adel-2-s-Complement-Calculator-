//program a input file and create to 2 files, the first is the cubelist of the function and the second is the complement 
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
//you should provide your boolean func."the input" represented in aPCNCube List file just like the "part5.pcn" file or just in a text file,
//put the name of the file in the line number 548, the name of the cubelist output file in the line no. 646 and
//the name of the complement output file in line no. 674
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include <fcntl.h>
#include<mem.h>
#include<unistd.h>
int NumOfSlots=0;int NumOfCubes=0; int PosNum,NegNum;
int NumOfVarsThatMustBeANDed=0;
int Final_Matrix[1048576][20];//1048576=2^20
int Current_Row_In_Final_Matrix=0;
int AllSelectedVars[19];//it must be here , bec the previous place is caused rewriting at it 
int state_of_the_selected_vars_p[19];
int state_of_the_selected_vars_n[19];
int skip_p=0;
int skip_n=0;
bool sparing =0;
int p_done=0;
int sparing_p[1048576][20];
int rows_of_sparing_p=0;
//vars to know how many Cofactors the program create
int MaxPosCofaNum=0,MaxNegCofaNum=0;
int Max__Num_Of_Rows=0;//Max__Num_Of_Rows OF THE FINAL Solution
int PosCofaNum=1,NegCofaNum=1;
int v=0; //to know how many the orcc func is called

int find_most_binate_var (int list1 [][NumOfSlots],int rs,int*b)//b represent if the boolean func. is binate or not if b=1 then it's binate
{int Namevar;
int h=0,g,i,k;int appear[NumOfSlots];
int TureForm[NumOfSlots],FalseForm[NumOfSlots],binate[NumOfSlots];
int min_binate,IndexOfMax ,IndexOfMin,max_appear;
bool equalybinate =0,equalappear=0;
int lessIndexunate[NumOfSlots];
bool nobinate=0;

for (i=0;i<NumOfSlots;++i)
	{appear[i]=0;TureForm[i]=0;FalseForm[i]=0; binate[i]=0;
	for(k=0;k<rs;++k)
		{if (list1[k][i]==1) {++appear[i];++TureForm[i];}
		else if (list1[k][i]==0) {++appear[i];++FalseForm[i];}}	}

//obtain the binate state of all vars
for (i=0;i<NumOfSlots;++i) binate[i]=abs((TureForm[i]-FalseForm[i]));
	//remove it !!!!!!!!!
	for (i=0;i<NumOfSlots;++i)
	printf("binate[%d]=%d\n",i+1,binate[i]);
	printf("------\n");
	for (i=0;i<NumOfSlots;++i)
	printf("appear[%d]=%d\n",i+1,appear[i]);
	printf("------\n");	
	//stop removing 
//find max value in the appear array
max_appear=appear[0];
IndexOfMax=0;
for (i=1;i<NumOfSlots;++i)
	{if (appear[i]>max_appear)
	{max_appear=appear[i];
	IndexOfMax=i;}} 

//know how many element equal the max appear value 
k=0;//k represents how many element equal the max appear value 
for (i=0;i<NumOfSlots;++i)
{if (appear[i]==max_appear&&!(IndexOfMax==i)){equalappear=1; ++k;}}
//check if there is no a binate var
for (i=0;i<NumOfSlots;++i)
	{if(TureForm[i]==0||FalseForm[i]==0)
	 {lessIndexunate[h]=i;
	 	++h;}}
if (h==NumOfSlots)	{nobinate=1; *b=0;Namevar=IndexOfMax+1;  return Namevar;}
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
//print the indexes of the variables that have value equal to max_appear
for (i=0;i<k;++i)
	printf("lessIndexappear[%d]=%d...max_appear=%d\n",i,lessIndexappear[i],max_appear);printf("-------\n");
//obtain the binate value of all elements that their index in "lessIndexappear" array
int BinateOfMostAppear[k];
for (i=0;i<k;++i)	BinateOfMostAppear[i]=binate[lessIndexappear[i]];	
//print the binate value of the variables that have value equal to max_appear
for (i=0;i<k;++i)
	printf("BinateOfMostAppear[%d]=%d\n",i,BinateOfMostAppear[i]);printf("------\n");
//obtain the min value in the "BinateOfMostAppear" array
min_binate=BinateOfMostAppear[0];
IndexOfMin=0;
for (i=1;i<k;++i)
{if (BinateOfMostAppear[i]<min_binate)
	{min_binate=BinateOfMostAppear[i];
	IndexOfMin=i;}} 
printf("min_binate=%d  IndexOfMin=%d \n",min_binate,IndexOfMin);
//know how many element equal the min BinateOfMostAppear value 
int count=0;
for (i=0;i<k;++i)
{ if (BinateOfMostAppear[i]==min_binate&&!(IndexOfMin==i))	{equalybinate=1;  ++count;}}
if (equalybinate)
{//return the index of the first element that equal the min value in the binate and appear values  
equalybinate=0;
for (i=0;i<k;++i)
{if (binate[lessIndexappear[i]]==min_binate){ Namevar=lessIndexappear[i]+1;break;}}
 return Namevar;}
else
{Namevar=lessIndexappear[IndexOfMin]+1;
return Namevar;}

}
else {Namevar=IndexOfMax+1; return  Namevar;}
}

//a func return num of rows of the positiveCofactor cube list
int NumOfPosExistingRows(int list3[][NumOfSlots],int rs,int var)
{
printf("Data about The PosCofactor of Var[%d]:\n",var);
int k=0;
int NumFalseInTheCertainSlot=0;
var=var-1;
for(k=0;k<rs;++k)
	{if(list3[k][var]==0) ++NumFalseInTheCertainSlot;}
int NumOfRows=rs-NumFalseInTheCertainSlot;//number of the rows in the new array -->"Cofactor"array in "Cofactor" func.
//printf("number of the columns in the new /PosCofactor'num=%d'/ array=%d\n",PosCofaNum,NumOfRows);
return	NumOfRows;
}

//a func return num of rows of the NegitiveCofactor cube list
int NumOfNegExistingRows(int list3[][NumOfSlots],int rs,int var)
{
printf("Data about The NegCofactor of Var[%d]:\n",var);
int k=0;
var=var-1;
int NumTrueInTheCertainSlot=0;
for(k=0;k<rs;++k)
	{if(list3[k][var]==1) ++NumTrueInTheCertainSlot;}
int NumOfRows=rs-NumTrueInTheCertainSlot;//number of the rows in the new array -->"PosCofactor"array
//printf("number of the columns in the new /NegCofactor'num=%d'/ array=%d\n",NegCofaNum,NumOfRows);
return	NumOfRows;
}
//Cofactor func declaration
void Cofactor (int list3[][NumOfSlots],int rs,int var,int NumOfRows,char state ,int Cofactor[NumOfCubes][NumOfSlots])
{	int h,g,i,k=0;												    //state must be 'p' or 'n' 
	var=var-1;														// note that p & n are small characters	
//initializate the CubeList array(assuming all vars don't care)
for (h=0;h<NumOfRows;++h)
	{for (g=0;g<NumOfSlots;++g)
	 Cofactor[h][g]=2;}
//full the rest of the NegCofactor cubelist 
for(k=NumOfRows;k<NumOfCubes;++k)
	{for(i=0;i<NumOfSlots;++i)
		Cofactor[k][i]=4;}
//Obtain all indexes of all rows that will be existed in the new array
int IndexofExistingRow[NumOfRows];
int count=0;
if (state=='p')
{if(NumOfVarsThatMustBeANDed==0) goto skip; 
if(AllSelectedVars[(NumOfVarsThatMustBeANDed-1)]==(var+1)) 
goto skip;

for(i=0;i<NumOfVarsThatMustBeANDed;++i)
{if(AllSelectedVars[i]==(var+1)) 
{printf (" new cofactor\n"); 
NumOfVarsThatMustBeANDed=i; 
for(i;i<=19;++i)
{AllSelectedVars[i]=20;
state_of_the_selected_vars_p[i]=3;
state_of_the_selected_vars_n[i]=3;}
break; }}
skip:
AllSelectedVars[NumOfVarsThatMustBeANDed]=var+1;//to save name of the cofactor 
state_of_the_selected_vars_p[NumOfVarsThatMustBeANDed]=1;
state_of_the_selected_vars_n[NumOfVarsThatMustBeANDed]=1;
++NumOfVarsThatMustBeANDed;
	if(NumOfRows==0)//that means that cofactor is false 
	{for (g=0;g<NumOfSlots;++g)
	Cofactor[0][g]=3;
	goto h;}
	
for (k=0;k<rs;++k)
		{if (list3[k][var]==1||list3[k][var]==2) 
			{IndexofExistingRow[count]=k;
			++count;}}
	}
else
{if(AllSelectedVars[(NumOfVarsThatMustBeANDed-1)]==(var+1))
 goto skip1;

for(i=0;i<NumOfVarsThatMustBeANDed;++i)
{if(AllSelectedVars[i]==(var+1)) 
{ NumOfVarsThatMustBeANDed=i; printf (" new cofactor...\n");
for(i;i<=19;++i)
{AllSelectedVars[i]=20;
state_of_the_selected_vars_p[i]=3;
state_of_the_selected_vars_n[i]=3;}
break; }}
skip1:
AllSelectedVars[NumOfVarsThatMustBeANDed]=var+1;//to save name of the cofactor 
state_of_the_selected_vars_p[NumOfVarsThatMustBeANDed]=0;
state_of_the_selected_vars_n[NumOfVarsThatMustBeANDed]=0;
++NumOfVarsThatMustBeANDed;
if(NumOfRows==0)//that means that cofactor is false 
	{for (g=0;g<NumOfSlots;++g)
	Cofactor[0][g]=3;
	goto h;}
for (k=0;k<rs;++k)
		{if (list3[k][var]==0||list3[k][var]==2) 
			{IndexofExistingRow[count]=k;
			++count;}}
	}
		
//set the other slots in the new array
for (i=0;i<NumOfSlots;++i)
{	if (var!=i)
		{for (k=0;k<NumOfRows;++k)
		Cofactor[k][i]=list3[IndexofExistingRow[k]][i];}	}
h:
//printing the new array	
for	(k=0;k<NumOfCubes;++k)
{	for (i=0;i<NumOfSlots;++i)
		printf(" %d",Cofactor[k][i]);
	printf ("\n");	}	
printf("--------------|\n");
}
//a func. anded a variable with its cofactor 			 //1 OR 0
void ANDVC(int list3[][NumOfSlots],int NumOfRows,int var,int state )
{	//list3 is the cofactor//NumOfRows of the cofactor//"var"-->name of the var. and"state"-->is true of false 
if (NumOfRows!=0) //because if the cube has element == 3 then it is falue (0 and x = 0)
{
int i , k ;	printf("var=%d...AND Operation of state=%d\n",var,state);		
--var;																    
//do the AND operation based on the state of the var.
if (state==1 )
	{for (k=0;k<NumOfRows;++k)
		{	if (list3[k][var]==2)list3[k][var]=1;
			else {printf("Error: there is a True form or a False form, so the AND operation stops!!\n ");break;}}}
else
	{for (k=0;k<NumOfRows;++k)
			{if (list3[k][var]==2)list3[k][var]=0;
			else {printf("Error: there is a True form or a False form, so the AND operation stops!!\n ");break;}}}
}}
//--------------------
//func. concatenates 2 cube lists --> an OR operation 
void ORCC (int list1[][NumOfSlots],int NumRows1,int list2[][NumOfSlots],int NumRows2 )//this func full the Final_Matrix only.
{int i,k,h,g=0;
int TotalRows=NumRows1+NumRows2;
int r=Current_Row_In_Final_Matrix;
printf("r=%d  ",r);
Current_Row_In_Final_Matrix=Current_Row_In_Final_Matrix+TotalRows;
printf("Current_Row_In_Final_Matrix=%d\n",Current_Row_In_Final_Matrix);
if(NumRows1!=0&&NumRows2!=0)
{g=r;
// do the or operation
for (i=0;i<NumOfSlots;++i)
{//copy the first array in the result array 
for (k=0;k<NumRows1;++k)
{Final_Matrix[g][i]=list1[k][i];++g;}
// copy the second array 
for (h=0;h<NumRows2;++h)
{Final_Matrix[g][i]=list2[h][i];++g;}
g=r;}
}
else
{if(NumRows1==0)
//copy list2 in result 
{for (h=0;h<TotalRows;++h)
{for (i=0;i<NumOfSlots;++i)
Final_Matrix[r][i]=list2[h][i];
++r;}}
else
//copy list1 in result
{for (h=0;h<TotalRows;++h)
{for (i=0;i<NumOfSlots;++i)
Final_Matrix[r][i]=list1[h][i];
++r;}}}
//print the result array 
	printf("===========Final_Matrix at the ORCC func 'calling num (%d)'==========\n",v);++v;
	for(i=0;i<Current_Row_In_Final_Matrix;++i)
	{for (k=0;k<NumOfSlots;++k) printf(" %d",Final_Matrix[i][k]);
	printf("\n");}
	printf("======================================\n");
}						//list has one row !!!!				//rs=0!!
//-------------------------------------
int complement (int list[][NumOfSlots],int rs,int *NewNumOfRows, int output_matrix[NumOfCubes][NumOfSlots])
{int h,g,a=0,k=0,i; 
*NewNumOfRows=0;
//check if the cube list has a one cube that has all the vars don't care
for (h=0;h<NumOfCubes;++h)
	{if(list[h][0]==4) break;//'4' means that you reach to the end of the cube list.
	for(i=0;i<NumOfSlots;++i)
		{if (list[h][i]==2) ++a;}
	if (a==NumOfSlots) 
		{a=0;
		for(k=0;k<NumOfSlots;++k)
			output_matrix[0][k]=3; // it's mean that comp here Don't count-->"false"
		*NewNumOfRows=0;//It means that the "comp" will be empty
	//full the rest of this cubelist 
	for(k=((*NewNumOfRows)+1);k<NumOfCubes;++k)
		{for(i=0;i<NumOfSlots;++i)
			output_matrix[k][i]=4;}
		return 0;}
	else	
		a=0;}
a=0;//to reuse the count in another checking 
//if this cube list has no cube, then this represents the Boolean equation “0”.
if(rs==0)
	{for(k=0;k<NumOfSlots;++k)
		output_matrix[0][k]=2;
	*NewNumOfRows=1;
//full the rest of this cubelist 
for(k=(*NewNumOfRows);k<NumOfCubes;++k)
	{for(i=0;i<NumOfSlots;++i)
		output_matrix[k][i]=4;}	
	return 0;}
//Apply DeMorgan's law on an one cube or a product term
if (rs==1)
{int b,NumOfDontCareVarsInThisRow=0;
for(b=0;b<NumOfSlots;++b)
	{if(list[0][b]==2)	++NumOfDontCareVarsInThisRow;}// count the don't care vars in this row
*NewNumOfRows=NumOfSlots-NumOfDontCareVarsInThisRow;
//initializate the new CubeList array(assuming all vars don't care)
for (h=0;h<(*NewNumOfRows);++h)
	{for (g=0;g<NumOfSlots;++g)
		output_matrix[h][g]=2;}
//obtain the DeMorgan's cube list
int CurrentRow=0;
for(i=0;i<NumOfSlots;++i)
	{if(list[0][i]==1){output_matrix[CurrentRow][i]=0;	++CurrentRow;}
	else if (list[0][i]==0){output_matrix[CurrentRow][i]=1;	++CurrentRow;}}  
CurrentRow=0;
//full the rest of this cubelist 
for(k=(*NewNumOfRows);k<NumOfCubes;++k)
	{for(i=0;i<NumOfSlots;++i)
		output_matrix[k][i]=4;}
return 0;}	
//if the func not simple then ...do recursion
int binateVar=0,binateState=1;
int Final_num_of_rows_1;
int Final_num_of_rows_2;
binateVar=find_most_binate_var(list,rs,&binateState);//&binateState meaning, pass the address of the var. "binateState"
printf("binateVar=%d-------\n",binateVar);	
//print the entering cubelist to poscofactor
printf("list that enters poscofactor=\n");
for (i=0;i<NumOfCubes;++i)
	{for (k=0;k<NumOfSlots;++k)
		printf(" %d",list[i][k]);
	printf("\n");}
//Pos. cofactor 
PosNum= NumOfPosExistingRows(list,rs,binateVar);//when "PosNum" = 0 then the cofactor = 0
int PosCofactor[NumOfCubes][NumOfSlots];
Cofactor(list,rs,binateVar,PosNum,'p',PosCofactor);
skip_p=0;
int p[NumOfCubes][NumOfSlots];
complement(PosCofactor,PosNum,&Final_num_of_rows_1,p);
if(skip_p==0)
{++p_done;
if(p_done>=2)
{sparing =1;
printf("there is a sparing condition for p .. p_done=%d..and",p_done);
printf("sparing_p:\n");
for (i=0;i<NumOfCubes;++i)
	{for (k=0;k<NumOfSlots;++k)	
		printf(" %d",sparing_p[i][k]);
	printf("\n");	}}
//print p
if(p[0][0]!=4)//doesn't empty 
{printf("p=\n");
for (i=0;i<NumOfCubes;++i)
	{for (k=0;k<NumOfSlots;++k)
		printf(" %d",p[i][k]);
	printf("\n");}}}
//saving p for precaution
if(skip_p==0)
{if(p_done==1)
{rows_of_sparing_p=Final_num_of_rows_1;
for (i=0;i<NumOfCubes;++i)
	{for (k=0;k<NumOfSlots;++k)
		sparing_p[i][k]=p[i][k];}}}
//Neg. cofactor
//print the entering cubelist to negcofactor
printf("list that enters negcofactor=\n");
for (i=0;i<NumOfCubes;++i)
	{for (k=0;k<NumOfSlots;++k)
		printf(" %d",list[i][k]);
	printf("\n");}
skip_n=0;
NegNum= NumOfNegExistingRows(list,rs,binateVar);//when "NegNum" = 0 then the cofactor = 0
int NegCofactor[NumOfCubes][NumOfSlots];
Cofactor(list,rs,binateVar,NegNum,'n',NegCofactor);

int n[NumOfCubes][NumOfSlots];
complement(NegCofactor,NegNum,&Final_num_of_rows_2,n);	
//print n
if(skip_n==0)
{if(n[0][0]!=4)
{printf("n=\n");
for (i=0;i<NumOfCubes;++i)
	{for (k=0;k<NumOfSlots;++k)
		printf(" %d",n[i][k]);
	printf("\n");}}}
//obtain name of cofactor n and p 
if(skip_n==0)
{//the first case: the complement of the neg. cofactor of the first selected var. was calculated directly, after many calculations of the complement of the pos. cofactor
if (NumOfVarsThatMustBeANDed==1&&state_of_the_selected_vars_p==0&&state_of_the_selected_vars_n==0)
{ANDVC(n,Final_num_of_rows_2,AllSelectedVars[0],0);
goto finish;}
//the second case:the complement of the neg. cofactor and the pos. cofactor were calculated after many calculations or they were calculated directly 
int index_of_Repeated_var_name=20;
for(i=0;i<19;++i)
{if(AllSelectedVars[i]!=20&&AllSelectedVars[i+1]!=20){
if(AllSelectedVars[i]==AllSelectedVars[i+1])
{index_of_Repeated_var_name=i;	 break;}}}
if(index_of_Repeated_var_name!=20)
{state_of_the_selected_vars_n[index_of_Repeated_var_name]=0;
state_of_the_selected_vars_p[index_of_Repeated_var_name+1]=3;
state_of_the_selected_vars_n[index_of_Repeated_var_name+1]=3;
AllSelectedVars[index_of_Repeated_var_name+1]=20;
--NumOfVarsThatMustBeANDed;}
//go inside in the sparing condition only 
if(skip_n==0)
{if (sparing==1)
{//obtain the name of this extra p cofactor 
for(i=0;i<19;++i)
	{if(AllSelectedVars[i]==20)
		break;}
--i;
int name_of_the_extra_p	[i];
int state_of_the_name_of_the_extra_p[i];
for(k=0;k<=i;++k)
	{name_of_the_extra_p[k]=AllSelectedVars[k];
	state_of_the_name_of_the_extra_p[k]=state_of_the_selected_vars_p[k];}
//print its name 
printf("name_of_the extra_p:\n");
for(k=0;k<=i;++k) printf(" %d",name_of_the_extra_p[k]);
printf("\nstate_of_the_name_of_the extra_p:\n");
for(k=0;k<=i;++k) printf(" %d",state_of_the_name_of_the_extra_p[k]);
printf("\n");
//ANDed it 
for(k=0;k<=i;++k)
ANDVC(sparing_p,rows_of_sparing_p,name_of_the_extra_p[k],state_of_the_name_of_the_extra_p[k]);
//ORed 	it
ORCC(sparing_p,rows_of_sparing_p,n,0);
//set all variables that are used in the extra p cofactor to 0
sparing=0;
p_done=0;
//modify the name of the second p cofactor & the n cofactor
 int temp_AllSelectedVars[20];
 int temp_state_of_the_selected_vars_p[20];
 int temp_state_of_the_selected_vars_n[20];
 int count_p=0,d=0;
 for(k=i+2;k<20;++k)
 {if (AllSelectedVars[k]==20)break;
 else ++count_p;
 	temp_AllSelectedVars[d]=AllSelectedVars[k];
 	temp_state_of_the_selected_vars_p[d]=state_of_the_selected_vars_p[k];
 	temp_state_of_the_selected_vars_n[d]=state_of_the_selected_vars_n[k];
	 ++d;}
d=0;
state_of_the_selected_vars_p[i]=0;
for(k=i+1;k<count_p;++k)
	{AllSelectedVars[k]=temp_AllSelectedVars[d];
	state_of_the_selected_vars_p[k]=temp_state_of_the_selected_vars_p[d];
	state_of_the_selected_vars_n[k]=temp_state_of_the_selected_vars_n[d];
	++d;}
state_of_the_selected_vars_p[i]=0;	
 NumOfVarsThatMustBeANDed=count_p+i+1;
 printf("NumOfVarsThatMustBeANDed=%d\n",NumOfVarsThatMustBeANDed);
 index_of_Repeated_var_name=20;
for(i=0;i<19;++i)
{if(AllSelectedVars[i]!=20&&AllSelectedVars[i+1]!=20){
if(AllSelectedVars[i]==AllSelectedVars[i+1])
{index_of_Repeated_var_name=i;	 break;}}}
if(index_of_Repeated_var_name!=20)
{state_of_the_selected_vars_n[index_of_Repeated_var_name]=0;
state_of_the_selected_vars_p[index_of_Repeated_var_name+1]=3;
state_of_the_selected_vars_n[index_of_Repeated_var_name+1]=3;
AllSelectedVars[index_of_Repeated_var_name+1]=20;
--NumOfVarsThatMustBeANDed;}	
}	}
//print the name of the resulting cofactors
printf("AllSelectedVars:\n");
for(i=0;i<(NumOfVarsThatMustBeANDed+1);++i)
printf(" %d",AllSelectedVars[i]);
printf("\n");
printf("state_of_the selected_vars_p:\n");
for(i=0;i<(NumOfVarsThatMustBeANDed+1);++i)
printf(" %d",state_of_the_selected_vars_p[i]);
printf("\n");
printf("state_of_the selected_vars_n:\n");
for(i=0;i<(NumOfVarsThatMustBeANDed+1);++i)
printf(" %d",state_of_the_selected_vars_n[i]);
printf("\n");}
//and operation of p
if(skip_p==0)
{if (Final_num_of_rows_1!=0)
	{for(i=0;i<NumOfVarsThatMustBeANDed;++i)
		ANDVC(p,Final_num_of_rows_1,AllSelectedVars[i],state_of_the_selected_vars_p[i]);
//print the result 
printf("---p after the and operation:\n");
	for(i=0;i<Final_num_of_rows_1;++i)
		{for(k=0;k<NumOfSlots;++k)
			printf(" %d",p[i][k]);
	printf("\n");}}}
//and operation of n
if(skip_n==0)
{if (Final_num_of_rows_2!=0)	
	{for(i=0;i<NumOfVarsThatMustBeANDed;++i)
		ANDVC(n,Final_num_of_rows_2,AllSelectedVars[i],state_of_the_selected_vars_n[i]);
//print the result 
printf("---n after the and operation:\n");
for(i=0;i<Final_num_of_rows_2;++i)
	{for(k=0;k<NumOfSlots;++k)
		printf(" %d",n[i][k]);
printf("\n");}}}
finish:
if(skip_n==1)goto exit;	
if(skip_p==1){ORCC(p,0,n,Final_num_of_rows_2);
goto exit;}
ORCC(p,Final_num_of_rows_1,n,Final_num_of_rows_2);
*NewNumOfRows=Final_num_of_rows_1+Final_num_of_rows_2;
exit: 
skip_p=1;
skip_n=1;
//set all variables that are used in the extra p cofactor to 0
sparing=0;
p_done=0;
return 0;			
}
//==================
int main ()
{FILE *CubeListFile = fopen("part5.pcn","r");    	/// put the input file here "the boolean function".
int j=0,k=0,i=0;
int h,g,NumTheDontCareVars=0;
//make sure there is no an error in the reading operation
if (CubeListFile==NULL)
{printf("the file doesn't be read!\n");
return 0; }
else {printf("the reading operation is done!\n");
printf("---------------------------------\n");
}
// making an 2D array that represents a Cube List of the func.
char ch[3000];
char c[2];
char c1[6];
char c2[2]="  ";
//get the NumOfSlots
fgets(ch,1024,CubeListFile); // read a whole line from the file
NumOfSlots=atoi(ch);
printf("the variable ..NumOfSlots.. =%d\n",NumOfSlots);
//get the NumOfCubes 
fgets(ch,1024,CubeListFile);
NumOfCubes=atoi(ch);
printf("the variable...NumOfCubes..=%d\n",NumOfCubes );

MaxPosCofaNum=pow(2,NumOfSlots)/2,MaxNegCofaNum=pow(2,NumOfSlots)/2;
Max__Num_Of_Rows=MaxPosCofaNum+MaxNegCofaNum;
Final_Matrix[Max__Num_Of_Rows][NumOfSlots];

for (j=0;j<=19;++j){state_of_the_selected_vars_p[j]=3;
state_of_the_selected_vars_n[j]=3;//just initialize the state_of_the selected_vars arrays, and '3' means it is empty 
AllSelectedVars[j]=20;}//and initialize the AllSelectedVars array ,20 means it is empty
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
		
	if (full==1)
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
fclose(CubeListFile);
// printing the obtained cube list to an user
FILE *write_file=fopen("CubeListOfpart5.txt","w+");					///put the saving file here (the cube list of the boolean function)
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
	fflush(write_file);
	fclose(write_file);
int NumOfRowsOfFinal_result=0;
int mat[NumOfCubes][NumOfSlots];
int sparing_p[NumOfCubes][NumOfSlots];

complement(CubeList,NumOfCubes,&NumOfRowsOfFinal_result,mat);//the complement func. obtains the comlement value of the given boolean function   
// covert the final result into the input type
int rows=Current_Row_In_Final_Matrix;
printf("Current_Row_In_Final_Matrix=%d\n",Current_Row_In_Final_Matrix);

int numOfTheDontCareVarsInEveryRow[rows];
for(i=0;i<rows;++i)
	{numOfTheDontCareVarsInEveryRow[i]=0;
	for(k=0;k<NumOfSlots;++k)
		{if (Final_Matrix[i][k]!=2)		++numOfTheDontCareVarsInEveryRow[i];}}
//print the final result in a file, and convert the data in final_matrix into the type of the input file
int txt = open("ComplementOfpart5.txt",O_WRONLY|O_CREAT);
if(txt==-1)	
{printf("There is an error:delete the Complement file\n");
return 0;}

char e[3];
	itoa(NumOfSlots,e,10);printf("NumOfSlots=%c%c\n",e[0],e[1]);
write(txt,&e,sizeof(e));
	char e1[1]="\n";
write(txt,&e1,sizeof(e1));
	char e22[3];
	itoa(rows,e22,10);
write(txt,&e22,sizeof(e22));
	char e11[1]="\n";
write(txt,&e11,sizeof(e1));
char e2[1];
char e6[2];
char e3[1]=" ";
char e4[1]="-";
for(i=0;i<rows;++i)
	{if(numOfTheDontCareVarsInEveryRow[i]>=10)
		{itoa(numOfTheDontCareVarsInEveryRow[i],e6,10);
		write(txt,&e6,sizeof(e6));}
	else
		{itoa(numOfTheDontCareVarsInEveryRow[i],e2,10);
		write(txt,&e2,sizeof(e2));}
	for(k=0;k<NumOfSlots;++k)
		{if (Final_Matrix[i][k]==1)
		{write(txt,&e3[0],sizeof(e3[0]));
			if((k+1)>=10)
				{itoa((k+1),e6,10);
				write(txt,&e6,sizeof(e6));}
			else	
				{itoa((k+1),e2,10);
				write(txt,&e2,sizeof(e2));}}		
		else if (Final_Matrix[i][k]==0) 
		{write(txt,&e3[0],sizeof(e3[0]));
		write(txt,&e4[0],sizeof(e4[0]));
			if((k+1)>=10)
				{itoa((k+1),e6,10);
				write(txt,&e6,sizeof(e6));}
			else	
				{itoa((k+1),e2,10);
				write(txt,&e2,sizeof(e2));}}}
char e111[1]="\n";
write(txt,&e111[0],sizeof(e1));}
	char e1111[1]="\n";
write(txt,&e1111,sizeof(e1));
return 0;
}
