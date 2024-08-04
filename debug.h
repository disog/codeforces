using std::filesystem::path;

#define debug println

/**
 * Loads the input file
 */
#define init()                                                                 \
  auto _ =                                                                     \
      freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
