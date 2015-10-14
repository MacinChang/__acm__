void manacher(){
    int res = 0, id = 0;
    for(int i = 0; i < m; i++) {
        if(mx > i){
            p[i] = min(p[2 * id - i], mx - i);
        }
        else{
            p[i] = 1;
        }
        //p[i] = mx > i? min(mp[2*id-i], mx-i): 1;
        while(s[i + p[i]] == s[i - p[i]]){
            p[i]++;
        }
        //while(s[i+mp[i]] == s[i-mp[i]]) mp[i]++;
        if(i + p[i] > res) {
            res = i + p[i];
            id = i;
        }
    }
}
