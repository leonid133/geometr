#ifdef FIG_EXPORTS
#define FIG_API __declspec(dllexport)
#else
#define FIG_API __declspec(dllimport)
#endif

namespace Fig
{
    class Fig
    {
        public: 
        static FIG_API Geometr::Triangle Init();
    };
   
}