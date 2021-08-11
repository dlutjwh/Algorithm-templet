#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
#include<deque>
#include<stack>
#include<unordered_set>
#include<queue>
#include<unordered_map>
#include<cmath>
using namespace std;
#define ll long long


struct tree_node{
    vector<float> cur_point;  //最后一个元素为在原始数据中的id
    int split;
    tree_node *left,*right;
    tree_node(vector<float> &p,int dim):split(dim),left(nullptr),right(nullptr),cur_point(p){}
};

class KdTree{
    public:
    tree_node *GetRoot(){  //后面把root变为private
        return root;
    }
    void first_dfs(tree_node *cur){  //先序输出节点
        if(!cur)
            return ;
        for(int i=0;i<cur->cur_point.size();i++)
            cout<<cur->cur_point[i]<<" ";
        cout<<endl;
        first_dfs(cur->left);
        first_dfs(cur->right);
    }

    void test(){
        first_dfs(root);
    }

    float Dis(vector<float> &source){  //计算距离
        float sum=0;
        for(int i=0;i<source.size()-1;i++)
            sum = sum+(source[i]- target_point[i])*(source[i]- target_point[i]);
        return sqrt(sum);
    }

    void FindNearest(tree_node *cur){
        if(cur==nullptr)
            return ;
        /*
        cout<<-1<<" ";
        for(int i=0;i<2;i++)
            cout<<cur->cur_point[i]<<" ";
        cout<<endl;
        */
        bool left = 0;
        if(target_point[cur->split]<=cur->cur_point[cur->split] ){
            left = 1;
            FindNearest(cur->left);
        }
        else FindNearest(cur->right);

        if(Dis(cur->cur_point)<min_dis){
            min_dis= min(min_dis,Dis(cur->cur_point));
            Nearest_id = cur->cur_point[cur->cur_point.size()-1];
        }
        if( min_dis>fabs(cur->cur_point[cur->split]- target_point[cur->split])){
            if(left)
                FindNearest(cur->right);
            else FindNearest(cur->left);
        }
    }
    int NearestPoint(vector<float> p){
        min_dis = 1e9;
        target_point.assign(p.begin(),p.end());
        FindNearest(root);
        return min_dis;
    }

    KdTree(vector<vector<float> > &ps){
        n_features = ps[0].size();
        points.assign(ps.begin(),ps.end());
        for(int i=0;i<points.size();i++)
            points[i].push_back(i);   //把id放进去
        pre_points.assign(ps.begin(),ps.end());
        root = BuildTree(0,points.size()-1);
    }

    tree_node *BuildTree(const int &lIndex,const int &rIndex);
    int Nearest_id;
    int FindSplitDim(const int &lIndex,const int &rIndex);
    int n_features;   //维度
    vector<vector<float> > points;
    vector<vector<float> > pre_points; //原始点
    tree_node *root = nullptr;
    float min_dis = 1e9;  //最小距离
    vector<float> target_point;
};

int KdTree::FindSplitDim(const int &lIndex,const int &rIndex){  //极值差最大的作为分割维度
    if(rIndex-lIndex<=1)
        return 0;
    int cur_best_dim = 0;
    float cur_largest_spread = -1;
    float cur_min_val;
    float cur_max_val;
    for (int dim = 0; dim < n_features; ++dim) {
        cur_min_val = points[lIndex][dim];
        cur_max_val = points[lIndex][dim];
        for (int id = lIndex ;id<= rIndex;id++) {
            if (points[id][dim] > cur_max_val)
                cur_max_val = points[id][dim] ;
            else if (points[id][dim]  < cur_min_val)
                cur_min_val = points[id][dim];
        }

        if (cur_max_val - cur_min_val > cur_largest_spread) {
            cur_largest_spread = cur_max_val - cur_min_val;
            cur_best_dim = dim;
        }
    }
    return cur_best_dim;
}
tree_node *KdTree::BuildTree(const int & lIndex,const int &rIndex){
    int dim = FindSplitDim(lIndex,rIndex);
    nth_element(points.begin()+lIndex, points.begin()+(rIndex+lIndex)/2  ,points.begin()+rIndex+1 , \
                [dim](const vector<float> &a,const vector<float> &b){return a[dim]<b[dim];});
    tree_node * cur_node = new tree_node(points[ (rIndex+lIndex)/2],dim);

    if((rIndex+lIndex)/2>lIndex)
        cur_node->left = BuildTree(lIndex,(rIndex+lIndex)/2-1);
    if((rIndex+lIndex)/2<rIndex)
        cur_node->right = BuildTree((lIndex+rIndex)/2+1,rIndex);
    return cur_node;
}


int main(){

    vector<vector<float> > vec={{2,3},{5,4},{9,6},{4,7},{8,1},{7,2} } ;
    KdTree tree(vec);
    tree.NearestPoint(vector<float>{4,6});
    cout<<tree.min_dis<<endl;
    for(int i=0;i<vec[tree.Nearest_id].size();i++)
    cout<<vec[tree.Nearest_id][i]<<endl;
    //tree.test();
    return 0;
}
