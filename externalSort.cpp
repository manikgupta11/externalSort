#include <bits/stdc++.h> 
using namespace std; 
  
class Node { 
    public:
    int i; 
    int element; 
}; 
  
class MinHeap {
    public:  
    Node* arr; // pointer to array of elements in heap 
    int heap_size;

    // Constructor
    MinHeap(Node a[], int size){
        arr = a; 
        heap_size=size; 

        for(int i=heap_size/2;i>=0;i--){
            MinHeapify(i); 
        } 
    }

    void MinHeapify(int i){
        int left=(2*i)+1;  //left child
        int right=(2*i)+2;;  //right child
        int smallest=i; 
        //check if left or right is smallest
        if (left < heap_size ){ 
            smallest = (arr[left].element < arr[smallest].element)? left:smallest; 
        }
        if (right < heap_size ){
            smallest = (arr[right].element < arr[smallest].element)? right:smallest; 
        }  
        //If either left or right is small, swap
        if (smallest != i) { 
            Node temp = arr[i]; 
            arr[i]=arr[smallest];
            arr[smallest]=temp; 
            MinHeapify(smallest); 
        }
    } 
}; 

//merge algorithm
void merge(int arr[], int l, int m, int r) { 
    int i=0; 
    int j=0; 
    int k=l; 
    int n1=m-l+1 ; 
    int n2= r-m; 

    int L[m-l+1], R[r-m]; 
 
    for (int i=0; i<n1; i++) {
        L[i]=arr[l + i]; 
    }
    for (int j=0; j<n2; j++) {
        R[j]=arr[m + 1+ j]; 
    }
  
    while (i<n1 && j<n2) { 
        if(L[i]<R[j]) { 
            arr[k++]=L[i++]; 
        } 
        else{ 
            arr[k++]=R[j++]; 
        } 
       
    } 
   while(j<n2) { 
        arr[k++] = R[j++]; 
    } 
 
    while(i<n1){ 
        arr[k++] = L[i++]; 
    }    
} 
  
  
void mergeSort(int arr[],int low,int high) { 
    if(low<high) { 
        int mid=(low+high)/2; 
  
        mergeSort(arr, low, mid); 
        mergeSort(arr, mid+1,high); 
  
        merge(arr,low,mid,high); 
    } 
} 
  

void mergeFiles(char *output_file, int n, int k) { 
    FILE* in[k]; 
    for (int i = 0; i < k; i++) { 
    string temp = to_string(i);
    char name[2];
    strcpy(name, temp.c_str());     
     in[i]=fopen(name,"r");
    } 

    FILE *out = fopen(output_file, "w"); 
  
    // Create minheap with k nodes. 
    // Every heap node  has first element of output file 
    
    Node* arr = new Node[k]; 
    
    int isize=0; 
    for(int i=0;i<k;i++) {  
        int res= fscanf(in[i], "%d ", &arr[i].element);
        
        if(res==1){ 
             arr[i].i=i;   //one number read successfully
         }
         else{
            break;         //break if empty file
        } 
        isize++;
  
    } 
    MinHeap heap1(arr,isize); //create heap 
  
    int count=0; 
  
    while (count!=isize) { 
       
        fprintf(out, "%d ", heap1.arr[0].element); //store min in output file
  
        int res=fscanf(in[heap1.arr[0].i], "%d ", &heap1.arr[0].element);
        if (res!=1) { 
            heap1.arr[0].element = INT_MAX; //Making it max so it moves in end
            count++; 
        } 

        arr[0]=heap1.arr[0];  //Replace root with next min element
        heap1.MinHeapify(0);  //Minheapify on root
       
    } 
  

    for (int i=0; i<k; i++){
        fclose(in[i]); //close input files
    }
  
    fclose(out); //close output file
} 

void split_merge(char *input_file,char *output_file,int nc){
    fstream file1;
    int count=0; int wc=0; 
    fstream file[nc]; 
    string word; 
    //   char input_file[] = "sort1"; 
    file1.open(input_file); 
    while(file1>>word){
        wc++;           //Counting numberss in file
    }
   int size=(int)ceil((float)wc/(float)nc);  //Finding numbers in each file
    file1.close();
    file1.open(input_file); 
    for(int i=0;i<nc;i++) {
      count=0;
      file[i].open(to_string(i),ios::out);        //opening file for write
      while (count<size && file1 >> word ) {     //write fill till size complete
        file[i]<<word;
        file[i]<<" "; 
        count++;
      } 

      file[i].close();
   }

   file1.close();
   for(int i=0;i<nc;i++){
     wc=0;                                       
     file[i].open(to_string(i),ios::in);
     while(file[i]>>word) {  
         wc++;             //word count of each created output file
     }
   
    file[i].close();
    file[i].open(to_string(i),ios::in);  //opening files to read for sort  
    int arr[wc]={0};                     //initializing array to be sorted
    int j=0;
    while (file[i] >> word ) { 
      arr[j]=stoi(word);                 //read file word by word anad store integers in array
      // cout<<arr[j]<<" ";
      // cout<<i<<" ";
      j++;
     } 
     file[i].close();
     file[i].open(to_string(i),ios::out|ios::trunc);    //open in trunc mode to clear file if it exist already
     file[i].close();
     file[i].open(to_string(i),ios::app);                //open file in append mode to store numbers
      mergeSort(arr,0,wc-1);                               //sort array
  
     //cout<<arr[6]<<" ";
     for (int k=0;k<wc;k++){
        file[i]<<to_string(arr[k]);                   //writing numbers in array to file 
        file[i]<<" ";
    }
     file[i].close();
 }    
 mergeFiles(output_file, size, nc);             //Merge output files


}


int main(int argc,char* argv[]) {     
    if(argc!=3){
        cout<<"Less arguments\nFormat:./a.out inputfile outputfile\n";
    }
    else{
      char* input_file = argv[1];
      char* output_file = argv[2];
      int nc=5;
      split_merge(input_file,output_file,nc);
  }
  
    // FILE* in = fopen(input_file, "w"); 
  
    // srand(time(NULL)); 
  
    // // generate input 
    // for (int i = 0; i <1000; i++) 
    //     fprintf(in, "%d ", rand()%1000); 
  
    // fclose(in); 

    return 0; 
} 