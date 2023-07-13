#include "Object.h"
#include "Party.h"
#include "Skill.h"
#include <algorithm>
#include <iostream>
#include "commandq.h"
#include "command.h"
Object::Object( const char* name)
{
    m_prevAttackTick = -1;
    m_hp = 0;

    m_damage = 0;
    m_attackSpeed = 0;

    m_party = nullptr;

    m_name = name;
}
Object::~Object()
{
    for (auto skill : m_skillList)
        delete skill;

    m_skillList.clear();

    //std::cout << "~Object" << std::endl;
}
void Object::updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy, Party* ourTeam) {

    if (isDead())
        return;

    //물리 공격
    if (m_prevAttackTick == -1)
    {
        m_prevAttackTick = nowTick;
        //enemy->damaged(m_damage, getName());

        cmdQ.push_back(m_prevAttackTick, new CCmdDamage(enemy, this, m_damage));

    }
    else {
        while (nowTick >= m_prevAttackTick + m_attackSpeed) {
            m_prevAttackTick += m_attackSpeed;

            cmdQ.push_back(m_prevAttackTick, new CCmdDamage(enemy, this, m_damage));
            //enemy->damaged(m_damage, getName());
        }
    }

    std::for_each(m_skillList.begin(), m_skillList.end(), [&]( Skill* skill) -> void{
        skill->updateFrame(cmdQ, nowTick, enemy, ourTeam, this);
    });
        // 단일 공격,전체 공격, 일부 공격
}

//void Object::damagedAll(int damage, std::string& attacker )
//{
//    if (m_party == nullptr) {
//        damaged(damage, attacker );
//    }
//    else {
//        m_party->damagedAll(damage, attacker);
//    }
//}
//
//void Object::healAll(int hp, std::string& healer ) {
//    if (m_party == nullptr) {
//        heal(hp, healer );
//    }
//    else {
//        m_party->healAll(hp, healer );
//    }
//}

bool Object::damaged(int damage, std::string& attacker ) {

    if (isDead()) {
        return false;
    }

    m_hp -= damage;

 //   std::cout << m_name <<"(hp:" << std::to_string(m_hp) << ") is Damaged(damage:" << std::to_string(damage) <<") from " << attacker << std::endl;

    if( isDead() )
        std::cout << m_name << " is Dead" << std::endl;

    return true;
}

bool Object::heal(int _hp, std::string& healer) {
    if (isDead()) {
        return false;
    }

    m_hp += _hp;

//    std::cout << getName() << "(HP:" << std::to_string(m_hp) << ") is Healed(hp:" << std::to_string(_hp) << ")  from " << healer << std::endl;
    return true;
}
