#include <iostream>
#include <vector>
#include <iomanip>

class BookStats {
    public:
        BookStats()
            : pages_by_user_(100000,0)
            , users_by_page_(1000,0)
        {}

        void AddStat(int user_id, int page){
            int begin = pages_by_user_[user_id]+1;
            pages_by_user_[user_id] = page;
            for (int i = begin; i <= page; ++i){
                ++users_by_page_[i];
            }
        }

        double GetStat(int user_id) const {
            int page = pages_by_user_[user_id];
            int user_count = users_by_page_[1];
            if (page == 0){
                return 0;
            }
            if (users_by_page_[page] == 1) {
                return 1;
            }
            int less_than_user = user_count - users_by_page_[page];
            return static_cast<double>(less_than_user)/static_cast<double>(user_count-1);
        }

    private:
        std::vector<int> pages_by_user_;
        std::vector<int> users_by_page_;
};

void ReadRequestAndPrint(BookStats& stats) {
    std::string request;
    int user_id;
    int page;
    std::cin >> request;
    if (request == "READ"){
        std::cin >> user_id >> page;
        stats.AddStat(user_id,page);
    } else if (request == "CHEER"){
        std::cin >> user_id;
        std::cout << std::setprecision(6) << stats.GetStat(user_id) << std::endl;
    }
}

int main () {
    int request_count;
    BookStats stats;
    std::cin >> request_count;
    for (int i = 0; i < request_count; ++i){
        ReadRequestAndPrint(stats);
    }
}