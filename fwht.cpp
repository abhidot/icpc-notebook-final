namespace fwht{
 template<typename T>
 void hadamard_xor(vector<T> &a){
  int n = a.size();
  for(int k = 1 ; k < n ; k <<= 1){
   for(int i = 0 ; i < n ; i += 2*k){
    for(int j = 0 ; j < k ; j++){
     T x = a[i + j];
     T y = a[i + j + k];
     a[i + j] = x + y;
     a[i + j + k] = x - y;}}}}
 template<typename T>
 void hadamard_or(vector<T> &a,bool inverse){
  int n = a.size();
  for(int k = 1 ; k < n ; k <<= 1){
   for(int i = 0 ; i < n ; i += 2*k){
    for(int j = 0 ; j < k ; j++){
     T x = a[i + j];
     T y = a[i + j + k];
     if(inverse){
      a[i + j] = x;
      a[i + j +k] = y - x;
     }
     else{
      a[i + j] = x;
      a[i + j + k] = x + y;}}}}}
 template<typename T>
 void hadamard_and(vector<T> &a,bool inverse){
  int n = a.size();
  for(int k = 1 ; k < n ; k <<= 1){
   for(int i = 0 ; i < n ; i += 2*k){
    for(int j = 0 ; j < k ; j++){
     T x = a[i + j];
     T y = a[i + j +k];
     if(inverse){
      a[i + j] = x - y;
      a[i + j + k] = y;
     }
     else{
      a[i + j] = x + y;
      a[i + j + k] = y;   }}}}}
 template<typename T>
 vector<T> multiply(vector<T> a,vector<T> b){
  int eq = (b==a);
  int n = 1 ;
  while (n < (int)max(a.size(),b.size())){
   n <<= 1;
  } 
  a.resize(n);
  b.resize(n);
  hadamard_xor(a);
  if (eq) b = a; else hadamard_xor(b);
  for(int i = 0 ; i < n ; i++){
   a[i]*=b[i];
  }
  hadamard_xor(a);
  T q = static_cast<T>(n);
  for(int i = 0 ; i < n ; i++){
   a[i]/=q;
  }
  return a;
 }}