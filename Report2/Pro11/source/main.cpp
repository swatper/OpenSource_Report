#include <iostream>
#include <map>
#include <string>
using namespace  std;
//Node 구조체
struct Node {
    string name;
    int midgrade;
    int fingrade;
};
//map은 자동 저렬함
map<string, Node> nodeMap;
// 탐색 함수
void print_node(const Node& node) {
    cout << "이름: " << node.name
         << ", 중간 성적: " << node.midgrade
         << ", 기말 성적: " << node.fingrade << "\n";
}
int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    int mid, fin;
    string name;
    Node node;
    cout << "노드 추가(이름 중간점수 기말점수): \n";
    while (cin >> name >> mid >> fin) {
        node.name = name;
        node.midgrade = mid;
        node.fingrade = fin;
        // map에 노드를 추가
        auto result = nodeMap.insert({name, node});
        if (result.second) {
            cout << name << "님 추가 완료\n";} 
        else {
            cout << name << "님 이미 존재\n";}
    }
    // 탐색 및 출력
    for (const auto& entry : nodeMap) {
        print_node(entry.second);}
    return 0;
}
