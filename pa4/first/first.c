#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//--------------------------------------GLOBAL VARIABLES---------------------------
int miss,hit,read,write;
struct matrixInfo** cache;
unsigned long long int usedAmount;
//---------------------THE THREE PIECES THAT NEED TO BE IN EACH ELEMENT OF THE MATRIX---------------
typedef struct matrixInfo{
unsigned long long int lasttimeUsed;
unsigned long long tag;
int filled;
}matrixInfo;

//-------------------------------WRITING WITH PREFETCH METHOD---------------------
int preWithWrite(unsigned long long tag,unsigned long long int setIndex,int assoc){
int leastUsed;
int i=0;
while(i<assoc){
// if the data in the matrix is not zero then you need to check what to kick out and what needs to be update 
if(cache[setIndex][i].filled!=0){
if(cache[setIndex][i].tag==tag){
return 0;
// do nothing here
}
if((i+1)==(assoc)){
read=read+1;
leastUsed=0;
int j=0;
while(j<assoc){
int check=cache[setIndex][j].lasttimeUsed;
int lowest=cache[setIndex][leastUsed].lasttimeUsed;
if(lowest>=check){
leastUsed=j;
}
j++;
}
usedAmount=usedAmount+1;
       	cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
cache[setIndex][leastUsed].tag=tag;
cache[setIndex][leastUsed].filled=1;
       	return 0;
}
}else{
read=read+1;
usedAmount=usedAmount+1;
cache[setIndex][i].tag=tag;
cache[setIndex][i].filled=1;
cache[setIndex][i].lasttimeUsed=usedAmount;
return 0;
}
i++;
}
 return 0;
}
//------------------------------REGULAR WRITE FOR FOR LRU---------------------------
int prereadFile(unsigned long long tag,unsigned long long int setIndex,int assoc){
int i=0;

while(i<assoc){
// check if it isnt zero and if it does equal the tag then dont do anything 
if(cache[setIndex][i].filled!=0){
if(cache[setIndex][i].tag==tag){
return 0;
}
// if it is at the end of the blocks it needs to go back and check which is the first one that is used so it can be kicked out

if(i==(assoc-1)){
read=read+1;
int leastUsed=0;
int j=0;
while(j<assoc){
int check=cache[setIndex][j].lasttimeUsed;
int lowest=cache[setIndex][leastUsed].lasttimeUsed;
if(lowest>=check){
leastUsed=j;
}
j++;
}
cache[setIndex][leastUsed].filled=1;
       	cache[setIndex][leastUsed].tag=tag;
       	usedAmount=usedAmount+1;
       	cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
       	return 0;
}
}else{
// if the element of the matrix is zero then you set the element and fill it and set the counter to how many times it was used
read=read+1;
usedAmount=usedAmount+1;
cache[setIndex][i].filled=1;
cache[setIndex][i].lasttimeUsed=usedAmount;
cache[setIndex][i].tag=tag;
return 0;
}
i++;
}
 return 0;
}
//-------------------------------REGULAR READ INTO-----------------------------
int readInto(unsigned long long  int tag,unsigned long long int setIndex,int assoc){
int leastUsed;
int i=0;
while(i<assoc){
// if the cache has the tag in it already then you add to the hits 
if(cache[setIndex][i].filled!=0){
if(cache[setIndex][i].tag==tag){
hit=hit+1;
return 0;
}
if(i==(assoc-1)){
miss=miss+1;
read=read+1;
leastUsed=0;
int j=0;
while (j<assoc){
int check= cache[setIndex][j].lasttimeUsed;
int lowest= cache[setIndex][leastUsed].lasttimeUsed;
if(lowest>=check){
leastUsed=j;
}
j++;
}
usedAmount=usedAmount+1;
      cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
      cache[setIndex][leastUsed].tag=tag;
cache[setIndex][leastUsed].filled=1;
      return 0;
}
}else{
// if it is empty then fill it up 
miss=miss+1;
read=read+1;
usedAmount=usedAmount+1;
cache[setIndex][i].lasttimeUsed=usedAmount;
cache[setIndex][i].filled=1;
cache[setIndex][i].tag=tag;
return 0;

}
i++;
}
 return 0;

}
//---------------------------------REGULAR WRITE INTO THE CACHE------------------------
int  writeinto(unsigned long long  int tag,unsigned long long int setIndex,int assoc){
int i=0;
while(i<assoc){
if(cache[setIndex][i].filled!=0){
// if its a write into then if the tag is the same as the element then you need to add a hit and a write.
if(cache[setIndex][i].tag==tag){
hit=hit+1;
write=write+1;
return 0;
}
if(i==(assoc-1)){
miss=miss+1;
read=read+1;
write=write+1;
int leastUsed=0;
int j=0;
while (j<assoc){
int check=cache[setIndex][j].lasttimeUsed;
int lowest= cache[setIndex][leastUsed].lasttimeUsed;
// if the least used element is more thant the element at the point then you kick it out and reset the lement to the new counter 
if(lowest>=check){
leastUsed=j;
}
j++;
}
usedAmount=usedAmount+1;
      cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
      cache[setIndex][leastUsed].tag=tag;
cache[setIndex][leastUsed].filled=1;
      return 0;
}
}else{
miss=miss+1;
read=read+1;
write=write+1;
usedAmount=usedAmount+1;
cache[setIndex][i].filled=1;
cache[setIndex][i].lasttimeUsed=usedAmount;
cache[setIndex][i].tag=tag;
return 0;
}
i++;
}
 return 0;
}
//-----------------------------------WRITE FOR THE PREFETCH------------------------------------
int prewrite(unsigned long long tag,unsigned long long int setIndex,int assoc,unsigned long long int pretag,unsigned long long int preSetIndex){
int i=0;
while(i<assoc){
if(cache[setIndex][i].filled!=0){
if(cache[setIndex][i].tag==tag){
hit=hit+1;
write=write+1;
return 0;
}
if(i==(assoc-1)){
miss=miss+1;
read=read+1;
write=write+1;
int leastUsed=0;
int j=0;
while(j<assoc){
int check=cache[setIndex][j].lasttimeUsed;
int lowest=cache[setIndex][leastUsed].lasttimeUsed;
if(lowest>=check){
leastUsed=j;
}
j++;
}
cache[setIndex][leastUsed].filled=1;
      cache[setIndex][leastUsed].tag=tag;
      usedAmount=usedAmount+1;
       	cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
// does prefetch when it is a write 
       	preWithWrite(pretag, preSetIndex,assoc);
       	return 0;
}
}else{
miss=miss+1;
read=read+1;
write=write+1;
usedAmount=usedAmount+1;
cache[setIndex][i].filled=1;
cache[setIndex][i].lasttimeUsed=usedAmount;
cache[setIndex][i].tag=tag;
// does the prefetch when it is a write
preWithWrite(pretag,preSetIndex,assoc);
return 0;
}
i++;
}
 return 0;
}
//-------------------------------------------PREFETCH READ-------------------------------
int preread(unsigned long long tag,unsigned long long int setIndex,int assoc,unsigned long long int pretag,unsigned long long int preSetIndex){
int i=0;
while(i<assoc){
if(cache[setIndex][i].filled!=0){
if(cache[setIndex][i].tag==tag){
hit=hit+1;
return 0;
}
if(i==(assoc-1)){
miss=miss+1;
read=read+1;
int leastUsed=0;
int j=0;
while(j<assoc){
int check=cache[setIndex][j].lasttimeUsed;
int lowest=cache[setIndex][leastUsed].lasttimeUsed;
if(lowest>=check){
leastUsed=j;
}
j++;
}
usedAmount=usedAmount+1;
      cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
cache[setIndex][leastUsed].filled=1;
      cache[setIndex][leastUsed].tag=tag;
// -------------READS THE FILE WITH REGULAR PREFETCH -------------
       	prereadFile(pretag,preSetIndex,assoc);
       	return 0;
}
}else{
miss=miss+1;
read=read+1;
usedAmount=usedAmount+1;
cache[setIndex][i].filled=1;
cache[setIndex][i].tag=tag;
cache[setIndex][i].lasttimeUsed=usedAmount;
// -------------READS THE FILE WITH REGULAR PREFETCH -------------
prereadFile(pretag,preSetIndex,assoc);
return 0;
}
i++;
}
return 0;
}
int main(int argc, char** argv){
int cachesize=atoi(argv[1]);
int blocksize=atoi(argv[4]);
  int n,numberOfSets,assoc,offset,index;
  char oper;
  unsigned long long int address,mask,tag,setIndex,pretag,preSetIndex,preaddress;
//-----------------------------------START OF FIFO------------------------------
if(argv[3][0]=='f'){

  FILE* fp;
  fp=fopen(argv[5],"r");
// -----------------------CHECKS TO SEE IF THE FILE IS EMPTY-----------------------------------
  if(fp==NULL){
    return 0;

}
// checking what kind of associativity is used nad the number of sets that are being used 
if(strcmp(argv[2],"direct")==0){
assoc=1;
numberOfSets=cachesize/blocksize;
}else if(argv[2][5]!=':'){
numberOfSets=1;
assoc=cachesize/blocksize;
}else{
    sscanf(argv[2],"assoc:%d",&n);
    assoc=n;
    numberOfSets=cachesize/blocksize/n;
  }
//------------------GETS BITS FOR OFFSET AND INDEX FOR RIGHT SHIFT--------------------------------
offset=log2(blocksize);
index=log2(numberOfSets);
mask=((1<<index)-1);
//-----------------------------MALLOCS SPACE FOR MATRIX------------------------------------------
int k=0;
cache=(matrixInfo**)malloc(numberOfSets*sizeof(matrixInfo*));
while(k<numberOfSets){
cache[k]=(matrixInfo*)malloc((assoc)*sizeof(matrixInfo));
k++;
}
k=0;
while(k<numberOfSets){
int l=0;
while(l<assoc){
cache[k][l].filled=0;
l++;
}
k++;
}
//-------------------------BEGINS THE WITH REGULAR AND NOT PREFETCH-------------------------
while(fscanf(fp, "%*x: %c %llx", &oper, &address)==2){
//-------------------------------GETS THE TAG AND INDEX---------------------------
setIndex=(address>>offset)&mask;
tag=address>>(offset+index);
if(strncmp(&oper,"W",1)==0){
writeinto(tag,setIndex,assoc);
}else if(strncmp(&oper,"R",1)==0){
readInto(tag,setIndex,assoc);
}
}
fclose(fp);
  fp=fopen(argv[5],"r");
  if(fp==NULL){
    return 0;
  }
//----------------------------------PRINTS WITHOUT PREFETCH VALUES ----------------------------
 	printf("no-prefetch\n");
printf("Memory reads: %d\n", read);
printf("Memory writes: %d\n", write);
printf("Cache hits: %d\n", hit);
printf("Cache misses: %d\n", miss);
//---------------------END OF REGULAR CACHING WITHOUT PREFETCH 
//---------------------resets the matrix to zero--------------
int i=0;
while (i<numberOfSets){
int j=0;
while (j<assoc){
cache[i][j].tag=0;
cache[i][j].filled=0;
cache[i][j].lasttimeUsed=0;
j++;
}
i++;
}
//----------------RESETS GLOBALS SO THEY ARE ZERO FOR PREFETCH----------------
miss=0;
hit=0;
read=0;
write=0;
usedAmount=0;
//---------------------STARTS THE PREFETCH --------------------------
while(fscanf(fp, "%*x: %c %llx", &oper, &address)==2){
//-----------GETS INDEX,TAG,OFFSET FOR THE PREFETCH---------------------
setIndex=(address>>offset)&mask;
tag=address>>(offset+index);
preaddress=address+blocksize;
preSetIndex=(preaddress>>offset)&mask;
pretag=preaddress>>(offset+index);
//----------------CHECKS WHETHER IT IS AN R OR W ----------------------
if(strncmp(&oper,"W",1)==0){
prewrite(tag,setIndex,assoc,pretag,preSetIndex);
}else if(strncmp(&oper,"R",1)==0){
preread(tag,setIndex,assoc,pretag,preSetIndex);
}

}
//--------------------------PRINTS OUT THE PREFETCH VALUES --------------------------------
 	printf("with-prefetch\n");
printf("Memory reads: %d\n", read);
printf("Memory writes: %d\n", write);
printf("Cache hits: %d\n", hit);
printf("Cache misses: %d\n", miss);
 
}
//-----------------------------------END OF PREFETCH ---------------------------------------
//--------------------------------LRU EXTRA CRECIT PART-----------------------------------------
else if (argv[3][0]=='l'){

  FILE* fp;
  fp=fopen(argv[5],"r");
  if(fp==NULL){
    return 0;
  }
//------------------GETS THE ASSOC AND THE NUMBER OF SETS--------------------------
if(strncmp(&oper,"direct",6)==0){
assoc=1;
numberOfSets=cachesize/blocksize;
}else if(argv[2][5]!=':'){
numberOfSets=1;
assoc=cachesize/blocksize;
}else{
    sscanf(argv[2],"assoc:%d",&n);
    assoc=n;
    numberOfSets=cachesize/blocksize/n;

  }
//--------------------GETS THE OFFSET AND THE INDEX---------------------------------
offset=log2(blocksize);
index=log2(numberOfSets);
mask=((1<<index)-1);
//-----------------------------CREATES CACHE FOR MATRIX----------------------------
cache=(matrixInfo**)malloc(numberOfSets*sizeof(matrixInfo*));
int p=0;
while (p<numberOfSets){
cache[p]=(matrixInfo*)malloc((assoc)*sizeof(matrixInfo));
p++;
}
p=0;
while(p<numberOfSets){
int h=0;
while(h<assoc){
cache[p][h].filled=0;
h++;
}
p++;
}
//------------------------------STARTS GOING THROUGH THE ADDRESSES ------------------------------
while(fscanf(fp, "%*x: %c %llx", &oper, &address)==2){
setIndex=(address>>offset)&mask;
tag=address>>(offset+index);
if(strncmp(&oper,"W",1)==0){
int i=0;;
while(i<assoc){
	if (cache[setIndex][i].filled!=0){
		if (cache[setIndex][i].tag==tag){
			hit =hit +1;
			break;
		} if ((i+1)==assoc){
			miss=miss+1;
			read=read+1;
			write=write+1;
			int leastUsed=0;
			int j=0;
			while(j<assoc){
				int check=cache[setIndex][j].lasttimeUsed;
				int lowest=cache[setIndex][j].lasttimeUsed;
				if (check<lowest){
					leastUsed=j;
				}
			j++;
			}
		usedAmount=usedAmount+1;
		cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
		cache[setIndex][leastUsed].tag=tag;
		cache[setIndex][leastUsed].filled=1;
		break;
		}
	}
i++;
}
}else if(strncmp(&oper,"R",1)==0){
	int i=0;
	while(i<assoc){
		if (cache[setIndex][i].filled!=0){
			if (cache[setIndex][i].tag==tag){
				hit=hit+1;
				write=write+1;
				break;
			}
			if ((i+1)==assoc){
				miss=miss+1;
				read=read+1;
				int leastUsed=0;
				int j=0;
				while(j<assoc){
					int check=cache[setIndex][j].lasttimeUsed;
					int lowest = cache[setIndex][leastUsed].lasttimeUsed;
					if (check<lowest){
						leastUsed=j;
					}
				j++;
				}
				usedAmount=usedAmount+1;
				cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
				cache[setIndex][leastUsed].tag=tag;
				cache[setIndex][leastUsed].filled=1;
				break;
			}
			
		}
	i++;
	}
}
}
fclose(fp);
  fp=fopen(argv[5],"r");
// ----------------------------IF THE TRACE FILE IS EMPTY--------------------
  if(fp==NULL){
    return 0;
  }
//-------------------------PRINTS OUT VALUES FOR LRU NON-PREFETCH------------------------
  printf("no-prefetch\n");
printf("Memory reads: %d\n", read);
printf("Memory writes: %d\n", write);
printf("Cache hits: %d\n", hit);
printf("Cache misses: %d\n", miss);

//--------------------------RESETS MATRIX TO ZERO--------------------------------------
int i=0;
while (i<numberOfSets){
int j=0;
while (j<assoc){
cache[i][j].tag=0;
cache[i][j].filled=0;
cache[i][j].lasttimeUsed=0;
j++;
}
i++;
}
// -----------------------AGAIN RESETS GLOBALS TO ZERO--------------------------------
miss=0;
hit=0;
read=0;
write=0;
usedAmount=0;
//----------------------------BEINGS PREFETCH LRU--------------------------------------
while(fscanf(fp, "%*x: %c %llx", &oper, &address)==2){
// setting the digits needed to get the offset and the index and the tag data 
setIndex=(address>>offset)&mask;
tag=address>>(offset+index);
preSetIndex=(preaddress>>offset)&mask;
pretag=preaddress>>(offset+index);
preaddress=address+blocksize;
// go through the file and asee if the oper is either W or R 
if(strncmp(&oper,"W",1)==0){
	int i=0;
	while(assoc>i){
	if (cache[setIndex][i].filled!=0){
	hit=hit+1;
	write=write+1;
	break;
	}	
	if ((i+1)==assoc){
		miss=miss+1;
		read=read+1;
		write=write+1;
		int leastUsed=0;
		int j=0;
		while(assoc>j){
		int check=cache[setIndex][j].lasttimeUsed;
		int lowest= cache[setIndex][leastUsed].lasttimeUsed;
		if (lowest>check){
			leastUsed=j;
		}
		j++;
		}
		usedAmount=usedAmount+1;
		cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
		cache[setIndex][leastUsed].tag=tag;
		cache[setIndex][leastUsed].filled=1;
		int k=0;
		while(assoc>k){
		if (cache[setIndex][k].filled!=0){
		break;
		}
		if ((i+1)==assoc){
			read=read+1;
			int leastUsed=0;
			int l=0;
			while(assoc>l){
			int check=cache[setIndex][l].lasttimeUsed;
			int lowest=cache[setIndex][leastUsed].lasttimeUsed;
			if (lowest>check){
				leastUsed=l;
			}	
			l++;
			}
			usedAmount=usedAmount+1;
			cache[setIndex][leastUsed].lasttimeUsed=usedAmount;
			cache[setIndex][leastUsed].tag=tag;
			cache[setIndex][leastUsed].filled=1;
			break;
		}
		k++;
		}
	}
	i++;
	}
	

}else if(strncmp(&oper,"R",1)==0){
}
}
//-----------------------PRINTS OUT THE PREFETCH LRU VALUES---------------------------------
 	printf("with-prefetch\n");
printf("Memory reads: %d\n", read);
printf("Memory writes: %d\n", write);
printf("Cache hits: %d\n", hit);
printf("Cache misses: %d\n", miss);
//----------------------------------END OF PREFETCH LRU---------------------------------
}
return 0;
}
//------------------------------------------------------------------------------------------

