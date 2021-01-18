#include "testlib.h"

using namespace std;

int n, m, k, cases;
vector<int> d;

string result;

bool readAns(InStream& stream) {
  int i, x, j, y;
  i = stream.readInt();
  if (i == -1) return false;

  vector<int> tot(n);
  int rep = 0;
  do {
    if (rep) i = stream.readInt(1, n);
    else if (i < 1 || i > n) stream.quitf(_wa, "#%d i = %d, out of range [1, %d]", cases, i, n);
    --i;
    x = stream.readInt(1, k);
    tot[i] += x;
    if (x < k) {
      int j = stream.readInt(1, n);
      if (i == --j) stream.quitf(_wa, "#%d i = j = %d", cases, i + 1);
      int y = stream.readInt(k - x, k - x);
      tot[j] += y;
    }
  } while (++rep < m);
  if (d != tot) {
    int i = 0;
    while (d[i] == tot[i]) ++i;
    stream.quitf(_wa, "#%d d[%d] = %d, but used %d", cases, i + 1, d[i], tot[i]);
  }

  return true;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int T = inf.readInt(1, 10);
  for (cases = 1; cases <= T; ++cases) {
    n = inf.readInt(1, 500);
    m = inf.readInt(max(1, n - 2), 5000);
    k = inf.readInt(1, 5000);
    d.resize(n);
    for (int i = 0; i < n; ++i)
      d[i] = inf.readInt(1, m * k);
    bool pans = readAns(ouf), jans = readAns(ans);
    if (pans != jans) {
      if (pans) quitf(_fail, "#%d, participant found answer, but jury didn't", cases);
      else quitf(_wa, "#%d, jury found answer, but participant didn't", cases);
    } else result.push_back(pans ? 'Y' : 'N');
  }
  quitf(_ok, "OK both got answer: %s", result.c_str());

  return 0;
}

