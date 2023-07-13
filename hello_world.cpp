//
// NAPI 헤더입니다.
// npm을 통해 node-addon-api를 로컬로 설치하면 ./node_modules 폴더에 같이 딸려옵니다.
// 이것을 설치하지 않고, 먼저 작업하면 include에 빨간줄이 그어집니다.
#include <napi.h>


#include <iostream>
#include <string>
#include <sstream>
#include <list>

#include "Party.h"
#include "Object.h"
#include "Skill.h"
#include "CommandQ.h"
#include "Command.h"

// pointer -> smart pointer로 바꿔야 한다.
Skill* MakeSkill(int type, int coolTime)
{
    Skill* newSkill = nullptr;
   // std::cout << type << ", " << coolTime << std::endl;
    switch (type)
    {
    case 1:
        newSkill = new SkillDamage("1", coolTime);
        break;
    case 2:
        newSkill = new SkillHeal("2", coolTime);
        break;
    case 3:
        newSkill = new SkillDamageWide("3", coolTime);
        break;
    case 4:
        newSkill = new SkillHeal("4", coolTime);
        break;
    default:
        throw std::runtime_error("Invalid Skill Type");
        break;
    };
    return newSkill;
}

void test(std::string& result, std::vector<int>& p1_value, std::vector<int>& p2_value){
    
    auto p1 = new Party("a");
    auto p2 = new Party("b");

    try {
        auto iterA = p1_value.begin();
        do {
            auto member = new Object("a1");
            member->setStat(*iterA, *(iterA + 1), *(iterA + 2)); std::advance(iterA, 3);
            member->addSkill(MakeSkill(*(iterA), *(iterA + 1))); std::advance(iterA, 2);
            member->addSkill(MakeSkill(*(iterA), *(iterA + 1))); std::advance(iterA, 2);
            member->addSkill(MakeSkill(*(iterA), *(iterA + 1))); std::advance(iterA, 2);
            member->addSkill(MakeSkill(*(iterA), *(iterA + 1))); std::advance(iterA, 2);

            p1->addMember(member);
            
        } while (iterA != p1_value.end());


        auto iterB = p2_value.begin();
        do {
            auto member = new Object("b1");

            member->setStat(*iterB, *(iterB + 1), *(iterB + 2)); std::advance(iterB, 3);
            member->addSkill(MakeSkill(*(iterB), *(iterB + 1))); std::advance(iterB, 2);
            member->addSkill(MakeSkill(*(iterB), *(iterB + 1))); std::advance(iterB, 2);
            member->addSkill(MakeSkill(*(iterB), *(iterB + 1))); std::advance(iterB, 2);
            member->addSkill(MakeSkill(*(iterB), *(iterB + 1))); std::advance(iterB, 2);

            p2->addMember(member);
        } while (iterB != p2_value.end());
    }
    catch(std::runtime_error e)
    { 
        std::cout << e.what() << std::endl;
    }    
    
    // 1tick == 1ms 이라고 가정하면 최대 100초동안 시뮬을 돌린다.
    int max = 1000 * 100;
    result = "time out";
    std::ostringstream sss;

    CommandQ cmdQ;

    for ( int i =0; i < max; i += 33 )
    {
        p1->updateFrame(cmdQ, i, p2);
        p2->updateFrame(cmdQ, i, p1);

        cmdQ.sort();

        for (size_t i = 0; i < cmdQ.size(); ++i)
        {
            std::tuple<int, Command*> item = cmdQ.at(i);
            Command* cmd = std::get<1>(item);
            cmd->Exec();
            delete cmd;
        }

        cmdQ.clear();

        if (p2->isDead()) {
            sss << "Elapsed Tick:" << i << ", Winner:" + p1->getName() + ", hp:" << p1->getHp() << " enemy hp:" << p2->getHp() << std::endl;
            result = sss.str();
            break;
        }

        if (p1->isDead()) {
            sss << "Elapsed Tick:" << i << ", Winner:" + p2->getName() + ", hp:" << p2->getHp() << " enemy hp:" << p1->getHp() << std::endl;
            result = sss.str();
            break;
        }
    }

   
    delete p1;
    delete p2;
}
//
// 자바스크립트의 String 객체를 반환하는 함수입니다.
// 파라미터는 info[n] 형태로 얻어올 수 있습니다.
Napi::String SayHi(const Napi::CallbackInfo& info) {
  //
  // info에는 현재 스코프 정보(env)도 들어있습니다.
  // 자바스크립트 객체를 생성하려면 반드시 이것부터 가져와야합니다.
  std::string result = "Error";
  Napi::Env env = info.Env();

  try{
      if( info.Length() < 2){
        throw std::runtime_error("invalid args count : require 2 Typedarray-Uint32Array");
      }

      Napi::Uint32Array buf1 = info[0].As<Napi::Uint32Array>();
      Napi::Uint32Array buf2 = info[1].As<Napi::Uint32Array>();

      std::vector<int> p1_values; p1_values.reserve( buf1.ElementLength());
      std::vector<int> p2_values; p2_values.reserve( buf2.ElementLength());
      
      for( auto i = 0; i < buf1.ElementLength();i++ ){
        p1_values.push_back(buf1.Get(i).ToNumber());
      }

      for( auto i = 0; i < buf2.ElementLength();i++ ){
        p2_values.push_back(buf2.Get(i).ToNumber());
      }

      test(result , p1_values, p2_values );
  }
  catch( std::runtime_error e)
  {
    result = e.what();
  }
  //
  // 현재 스코프 정보(env)와 std::string을 사용하여,
  // "Hi!"라는 자바스크립트 문자열을 반환합니다.
//   return Napi::String::New(env, result.c_str() );
  return Napi::String::New(env, result.c_str() );
  // return Napi::String::New(env, "Hi!");
}

//
// 애드온 이니셜라이져입니다.
// 자바스크립트 오브젝트(exports)에 함수를 하나씩 집어넣고,
// 다 집어넣었으면 리턴문으로 반환하면 됩니다.
Napi::Object init(Napi::Env env, Napi::Object exports) {
    //
    // 위의 함수를 "sayHi"라는 이름으로 집어넣습니다.
    exports.Set(Napi::String::New(env, "sayHi"), Napi::Function::New(env, SayHi));

    //
    // 다 집어넣었다면 반환합니다.
    return exports;
};

//
// 애드온의 별명과, 이니셜라이져를 인자로 받습니다.
NODE_API_MODULE(hello_world, init);