struct compress{
    map<int, int> zip;
    vector<int> unzip;

    compress(vector<int> &v){
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        unzip = vector<int>(v.size());
        for(size_t i = 0; i < v.size(); i++){
            zip[v[i]] = i;
            unzip[i] = v[i];
        }
    }
};
