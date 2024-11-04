#include<stdio.h>
#include<search.h>
#include<string.h>
#define TABLESIZE 20
//node 구조체
struct node{
    char *name;
    int midgrade;
    int fingrade;};
//전역 변수
char nametable[TABLESIZE * 20];  //이름을 저장할 테이블
struct node nodetable[TABLESIZE];//노드를 저장할 노드 테이블
struct node *root = NULL;        //Root 노드
//비교 함수
int Compare(const void *cp1, const void *cp2){
    return strcmp(((struct node *)cp1)->name , ((struct node *)cp2)->name);
}
//탐색 함수
void print_node(const void *nodeptr, VISIT order, int level){
    if(order == preorder || order == leaf){
        printf("이름 : %-20s, 중간 성적: %d, 기말 성적: %d \n",(*(struct node **)nodeptr)->name, 
                                                     (*(struct node **)nodeptr)->midgrade, 
                                                     (*(struct node **)nodeptr)->fingrade);}
}
//main
int main(){
    char *nameptr = nametable;
    struct node *nodeptr = nodetable;
    struct node **ret;
    int i = 0;
    //트리에 노드 추가
    printf("노드 추가(이름 중간점수 기말점수)\n");
    while (scanf("%s %d %d",nameptr,&nodeptr->midgrade, &nodeptr->fingrade)!= EOF && i++ < TABLESIZE){
        nodeptr->name = nameptr;
        ret = (struct node **)tsearch((void*)nodeptr,
                                      (void **)&root,
                                      (Compare));
        printf("%s님",(*ret)->name);
        if(*ret == nodeptr){
            printf(" 추가 완료\n");}
        else{
            printf(" 이미 존재\n");   }
        nameptr += strlen(nameptr) + 1;
        nodeptr++;
    }
    //탐색
    twalk((void*)root, print_node);
    return 0;
}
