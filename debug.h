using std::filesystem::path;

#define debug println
#define init(a)                                                                \
  auto _ = freopen(path(a).replace_filename("input").c_str(), "r", stdin);
