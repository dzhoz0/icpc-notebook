struct PerTrie{
    struct node{
        int cnt = 0;
        array<int, 2> child;
        node(){
            child.fill(-1);
        }
    };
    int id = 0;
    vector<node> tree;
    PerTrie(){
        tree.emplace_back();
    }
    int new_node(){
        ++id;
        if(id >= tree.size())tree.emplace_back();
        return id;
    }
    int add(int a, int prev){
        int cc = new_node();
        int cur = cc;
        tree[cur] = tree[prev];
        tree[cur].cnt++;
        for(int i=30; i>=0; --i){
            int val = (a >> i) & 1;
            int nxt = new_node();

            if(prev != -1 && tree[prev].child[val] != -1){
                tree[nxt] = tree[tree[prev].child[val]];
                prev = tree[prev].child[val];
            }
            else prev = -1;

            tree[cur].child[val] = nxt;
            cur = nxt;
            tree[cur].cnt++;
        }
        return cc;
    }
    int walk(int prev, int cur, int a){
        int ans = 0;
        for(int i=30; i>=0; --i){
            int val = 1 - ((a >> i) & 1);
            int num1 = (cur != -1 && tree[cur].child[val] != -1) ? tree[tree[cur].child[val]].cnt : 0;
            int num2 = (prev != -1 && tree[prev].child[val] != -1) ? tree[tree[prev].child[val]].cnt : 0;
            if(num1 - num2 > 0){
                ans |= (val << i);
                cur = (cur != -1) ? tree[cur].child[val] : -1;
                prev = (prev != -1) ? tree[prev].child[val] : -1;
            }
            else{
                ans |= ((1 - val) << i);
                cur = (cur != -1) ? tree[cur].child[1 - val] : -1;
                prev = (prev != -1) ? tree[prev].child[1 - val] : -1;
            }
        }
        return ans;
    }
};
