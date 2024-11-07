#define debug(x) cerr << #x <<" "; _prll(x); cerr << endl;

void _prll(int t) {
    cerr << t;
} 
void _prll(ll t) {
    cerr << t;
    } 
void _print(ll t) {
    cerr << t;
    } 
void _prll(string t) {
    cerr << t;
    } 
void _prll(char t) {
    cerr << t;
    } 
void _prll(lld t) {
    cerr << t;
    } 
void _prll(double t) {
    cerr << t;
    } 
void _prll(ull t) {
    cerr << t;
    } 
template <class T, class V> void _prll(pair <T, V> p); 
template <class T> void _prll(vector <T> v); 
template <class T> void _prll(set <T> v); 
template <class T, class V> void _prll(map <T, V> v); 
template <class T> void _prll(multiset <T> v); 
template <class T, class V> void _prll(pair <T, V> p) {
    cerr << "{"; _prll(p.fi); 
    cerr << ","; _prll(p.se); 
    cerr << "}";
    } 
template <class T> void _prll(vector <T> v) {
    cerr << "[ "; 
    for (T i : v) {
        _prll(i); 
        cerr << " ";
        } 
        cerr << "]";
        } 
template <class T> void _prll(set <T> v) {
    cerr << "[ "; for (T i : v) {_prll(i);
     cerr << " ";
     } 
     cerr << "]";
     } 
template <class T> void _prll(multiset <T> v) {
    cerr << "[ "; 
    for (T i : v) {
        _prll(i);
         cerr << " ";
         } 
         cerr << "]";
    } 
template <class T, class V> void _prll(map <T, V> v) {
    cerr << "[ "; 
    for (auto i : v) {
        _prll(i);
         cerr << " ";
         }
          cerr << "]";
    }

