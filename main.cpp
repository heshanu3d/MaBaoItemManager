#include <vector>
#include <string>
#include <regex>
#include <set>
#include <list>
#include <iostream>
#include <queue>
#include <deque>
#include <map>
#include <bitset>
#include <set>
using namespace std;

class MamaBaobao {
public:
    MamaBaobao(string str) : selfInfo(str) {}
    ~MamaBaobao() = default;
    void Add(string name, int num) {
        for (int i = 0; i < num; i++) {
            s.insert(name);
        }
    }
    void AddAll(const map<string, int>& m) {
        for (auto [name, num] : m) {
            for (int i = 0; i < num; i++) {
                s.insert(name);
            }
        }
    }
    void AddGiftList(const map<string, int>& m) {
        for (auto [name, num] : m) {
            for (int i = 0; i < num; i++) {
                s.insert(name);
                gift.insert(name);
            }
        }
    }
    void AddBuyList(const map<string, int>& m) {
        for (auto [name, num] : m) {
            for (int i = 0; i < num; i++) {
                s.insert(name);
                buy.insert(name);
            }
        }
    }
    void PrintAll() {
        cout << "[" << selfInfo << "]" << "清单:" << endl;
        ToString(s);
    }

    void ToString(const map<string, int>& res) {
        for (auto [name, num] : res) {
            cout << name << " : " << num << endl;
        }
        cout << endl;
    }

    // 直接受顺序容器
    template<typename T>
    void ToString(const T& v) {
        map<string, int> res;
        for (auto name : v) {
            res[name]++;
        }
        for (auto [name, num] : res) {
            cout << name << " : " << num << endl;
        }
        cout << endl;
    }
    string TypeInfo() {
        if (selfInfo.find("妈妈") != string::npos) {
            return "妈妈物品";
        } else if (selfInfo.find("宝宝") != string::npos) {
            return "宝宝物品";
        }
        return "";
    }

    template<typename T1, typename T2>
    std::vector<string> UnionApi(const T1& ms1, const T2& ms2) {
        std::vector<string> v(ms1.size() + ms2.size());
        auto it = set_union(ms1.begin(), ms1.end(), ms2.begin(), ms2.end(), v.begin());
        v.resize(it - v.begin());
        return v;
    }
    template<typename T1, typename T2>
    std::vector<string> DifferentApi(const T1& ms1, const T2& ms2) {
        std::vector<string> v(ms1.size() + ms2.size());
        auto it = set_difference(ms1.begin(), ms1.end(), ms2.begin(), ms2.end(), v.begin());
        v.resize(it - v.begin());
        return v;
    }
    void UnionAll(const MamaBaobao& maBao, bool needPrint=true) {
        auto v = UnionApi(s, maBao.s);
        if (needPrint) {
            cout << "[" << TypeInfo() << "总]清单:" << endl;
            ToString(v);
        }
    }
    void Different(const MamaBaobao& maBao) {
        auto buyUnion = UnionApi(buy, maBao.buy);
        auto v = DifferentApi(buyUnion, gift);
        cout << "[" << TypeInfo() << "额外购买]清单:" << endl;
        ToString(v);
    }

    string selfInfo;
    multiset<string> s;
    multiset<string> gift;
    multiset<string> buy;
};

void InitializeMama(MamaBaobao& hospital, MamaBaobao& yuesao) {
    map<string, int> listHospital = {
            make_pair("洗漱用品", 1),
            make_pair("吸管", 2),
            make_pair("毛巾", 2),
            make_pair("盆子", 2),
            make_pair("棉质睡衣", 2),
            make_pair("换洗衣服", 1),
            make_pair("梳子", 1),
            make_pair("发夹", 1),
            make_pair("产妇垫", 1),
            make_pair("卫生纸（卷）", 1),
            make_pair("拔奶器", 1),
            make_pair("防滑拖鞋（软底）", 1),
    };

    map<string, int> listYuesao = {
            make_pair("漱口水/月子牙刷", 1),
            make_pair("吸管", 1),
            make_pair("毛巾", 4),
            make_pair("盆子", 3),
            make_pair("杯子", 1),
            make_pair("棉质睡衣", 3),
            make_pair("袜子", 3),
            make_pair("刀纸", 3),
            make_pair("衣架", 10),
            make_pair("一次性护理垫（包）", 2),
            make_pair("一次性马桶垫（包）", 2),
            make_pair("一次性内裤（条）", 20),
            make_pair("卫生纸（卷）", 2),
            make_pair("夜用卫生巾（包）", 3),
            make_pair("肥皂", 1),
            make_pair("防滑拖鞋（软底）", 1),
    };
    hospital.AddBuyList(listHospital);
    yuesao.AddBuyList(listYuesao);
}

void InitializeBaobao(MamaBaobao& hospital, MamaBaobao& yuesao) {
    map<string, int> listHospitalGift = {
            make_pair("护脐带消毒药水", 1),
            make_pair("护脐带", 1),
            make_pair("背心", 1),
            make_pair("帽子", 1),
            make_pair("包被", 1),
            make_pair("衣服", 2),
    };
    map<string, int> listHospitalBuy = {
            make_pair("尿裤", 1),
            make_pair("湿纸巾", 1),
            make_pair("护臀膏", 1),
            make_pair("隔奶巾", 10),
            make_pair("小毛巾", 2),
            make_pair("小盆子", 2),
            make_pair("润肤膏", 1),
            make_pair("浴巾", 1),
            make_pair("大包被", 1),
            make_pair("奶瓶", 1),
            make_pair("奶粉（小罐）", 1),
            make_pair("换洗衣服（套，建议连体）", 3),
    };

    map<string, int> listYuesao = {
            make_pair("包被", 2),
            make_pair("绵柔纸巾", 3),
            make_pair("抽纸", 3),
            make_pair("护臀膏", 1),
            make_pair("口水巾", 10),
            make_pair("宝宝肥皂", 1),
            make_pair("宝宝衣架", 6),
            make_pair("宝宝盆", 2),
            make_pair("浴巾", 2),
            make_pair("奶瓶", 2),
            make_pair("奶瓶刷", 1),
            make_pair("奶瓶夹", 1),
            make_pair("不锈钢小盒子（装奶瓶头、奶瓶刷、架子、浸泡烫奶瓶）", 1),
            make_pair("奶粉（小罐）", 1),
            make_pair("尿不湿NB（包）", 1),
            make_pair("换洗衣服（套，建议连体）", 4),
    };
    hospital.AddGiftList(listHospitalGift);
    hospital.AddBuyList(listHospitalBuy);
    yuesao.AddBuyList(listYuesao);
}

int main()
{
    MamaBaobao mamaHospital("妈妈物品（医院）");
    MamaBaobao mamaYuesao("妈妈物品（月嫂）");
    InitializeMama(mamaHospital, mamaYuesao);
    mamaHospital.PrintAll();
    mamaYuesao.PrintAll();
    mamaHospital.UnionAll(mamaYuesao);
    mamaHospital.Different(mamaYuesao);

    MamaBaobao baobaoHospital("宝宝物品（医院）");
    MamaBaobao baobaoYuesao("宝宝物品（月嫂）");
    InitializeBaobao(baobaoHospital, baobaoYuesao);
    baobaoHospital.PrintAll();
    baobaoYuesao.PrintAll();
    baobaoHospital.UnionAll(baobaoYuesao);
    baobaoHospital.Different(baobaoYuesao);
    return 0;
}

