/*  Tests unitaires pour Dynamic_array<T>.
 *  Lab3 -- Dynamic_array générique
 *  INF3105 | Structures de données et algorithmes
 *  Professor: Eric Beaudry
 */

#include <iostream>
#include "dynamic_array.h"

bool test1(){
    std::cout << "test1() : ajouts simples" << std::endl;
    Dynamic_array<int> t;
    t.ajouter(3);
    t.ajouter(4);
    bool reussi = true;
    if(t[0] != 3){
        std::cout << " ==> ECHEC t[0]!=3" << std::endl;
        reussi=false;
    }
    if(t[1] != 4){
        std::cout << " ==> ECHEC t[1]!=4" << std::endl;
        reussi=false;
    }
    if(t.taille()!=2){
        std::cout << " ==> ECHEC Taille" << std::endl;
        reussi=false;
    }
    if(reussi)
        std::cout << " ==> OK" << std::endl;
    return reussi;
}

bool test2(){
    std::cout << "test2() : ajouts +" << std::endl;
    bool reussi = true;
    Dynamic_array<int> t;
    int n = 256*256;
    for(int i=0;i<n;i++)
        t.ajouter(i*2);

    if(t.taille()!=n){
        std::cout << " ==> ECHEC taille()" << std::endl;
        reussi = false;
    }

    for(int i=0;i<t.taille();i++)
        if(t[i] != i*2){
            std::cout << " ==> ECHEC : t[i]=" << t[i] << "!=" << (i*2) << std::endl;
            reussi = false;
        }
    if(reussi)
        std::cout << " ==> OK" << std::endl;
    return reussi;
}

bool test3(){
    std::cout << "test3() : operator =" << std::endl;
    Dynamic_array<int> t1;
    for(int i=0;i<10;i++)
        t1.ajouter(i);
    Dynamic_array<int> t2;
    t2 = t1;

    if(t2.taille()!=10){
        std::cout << " ==> ECHEC taille()" << std::endl;
        return false;
    }

    for(int i=0;i<10;i++)
        if(t2[i] != i){
            std::cout << " ==> ECHEC : t2[i]=" << t2[i] << "!=" << (i) << std::endl;
            return false;
        }

    std::cout << " ==> OK" << std::endl;
    return true;
}

bool test4(){
    std::cout << "test4() : operator =" << std::endl;
    Dynamic_array<int> t1;
    for(int i=0;i<10;i++)
        t1.ajouter(i);
    Dynamic_array<int> t2;
    t2 = t1;

    for(int i=0;i<10;i++)
        t1[i] = 0;
    t1.ajouter(0);

    if(t2.taille()!=10){
        std::cout << " ==> ECHEC taille()" << std::endl;
        return false;
    }

    for(int i=0;i<10;i++)
        if(t2[i] != i){
            std::cout << " ==> ECHEC : t2[i]=" << t2[i] << "!=" << (i) << std::endl;
            return false;
        }

    std::cout << " ==> OK" << std::endl;
    return true;
}

bool test5(){
    std::cout << "test5() : operator =" << std::endl;
    Dynamic_array<int> t1;
    for(int i=0;i<10;i++)
        t1.ajouter(i);
    Dynamic_array<int> t2;
    t2 = t1;
    t1.vider();
    for(int i=0;i<100;i++)
        t1.ajouter(i+1);
    t2 = t1;

    if(t2.taille()!=100){
        std::cout << " ==> ECHEC t2.taille()" << std::endl;
        return false;
    }

    for(int i=0;i<t2.taille();i++)
        if(t2[i] != i+1){
            std::cout << " ==> ECHEC : t2[i]=" << t2[i] << "!=" << (i+1) << std::endl;
            return false;
        }


    Dynamic_array<int> t3;
    for(int i=0;i<100;i++)
        t3.ajouter(i);
    Dynamic_array<int> t4;
    t4 = t3;
    t3.vider();
    for(int i=0;i<10;i++)
        t3.ajouter(i+1);
    t4 = t3;

    if(t4.taille()!=10){
        std::cout << " ==> ECHEC t4.taille()" << std::endl;
        return false;
    }

    for(int i=0;i<t4.taille();i++)
        if(t4[i] != i+1){
            std::cout << " ==> ECHEC : t4[i]=" << t4[i] << "!=" << (i+1) << std::endl;
            return false;
        }

    std::cout << " ==> OK" << std::endl;
    return true;
}

bool test6(){
    std::cout << "test6() : operator =" << std::endl;
    Dynamic_array<int> t1, t2;
    for(int i=0;i<100;i++)
        t1.ajouter(i);
    t1 = t1; // devrait être sans effet.
    if(t1.taille()!=100){
        std::cout << " ==> ECHEC taille()" << std::endl;
        return false;
    }

    for(int i=0;i<100;i++)
        if(t1[i] != i){
            std::cout << " ==> ECHEC : t1[i]=" << t1[i] << "!=" << (i) << std::endl;
            return false;
        }

    std::cout << " ==> OK" << std::endl;
    return true;
}

bool test7(){
    std::cout << "test7() : constructeur par copie" << std::endl;
    Dynamic_array<int> t1;
    for(int i=0;i<10;i++)
        t1.ajouter(i);
    Dynamic_array<int> t2(t1);

    if(t2.taille()!=10){
        std::cout << " ==> ECHEC taille()" << std::endl;
        return false;
    }

    for(int i=0;i<t2.taille();i++)
        if(t2[i] != i){
            std::cout << " ==> ECHEC : t2[i]=" << t2[i] << "!=" << i << std::endl;
            return false;
        }

    std::cout << " ==> OK" << std::endl;
    return true;
}

bool test8(){
    std::cout << "test8() : operator ==" << std::endl;
    Dynamic_array<int> t1;
    Dynamic_array<int> t2;
    for(int i=0;i<1024;i++){
        t1.ajouter(i);
        t2.ajouter(i);
    }

    t1.ajouter(3);
    bool ok = true;

    if(t1==t2){
        std::cout << " ==> ECHEC #1" << std::endl;
        ok = false;
    }
    if(t2==t1){
        std::cout << " ==> ECHEC #2" << std::endl;
        ok = false;
    }
    t2.ajouter(3);
    if(!(t1==t2)){
        std::cout << " ==> ECHEC #3" << std::endl;
        ok = false;
    }
    if(!(t2==t1)){
        std::cout << " ==> ECHEC #4" << std::endl;
        ok = false;
    }

    if(!(t1==t1)){
        std::cout << " ==> ECHEC #5" << std::endl;
        ok = false;
    }

    Dynamic_array<int> t3;
    if(t1==t3){
        std::cout << " ==> ECHEC #6" << std::endl;
        ok = false;
    }
    t3 = t2;
    if(!(t1==t3)){
        std::cout << " ==> ECHEC #6" << std::endl;
        ok = false;
    }

    if(ok)
        std::cout << " ==> OK" << std::endl;
    return ok;
}

bool test9(){
    std::cout << "test9() : insertion" << std::endl;
    Dynamic_array<int> t1;
    Dynamic_array<int> t2;
    for(int i=0;i<16;i++){
        t1.ajouter(i+1);
        t2.ajouter(i);
    }

    t1.inserer(0);
    t2.ajouter(16);

    bool ok = true;
    if(!(t1==t2)){
        std::cout << " ==> ECHEC #1" << std::endl;
        ok = false;
    }

    Dynamic_array<int> t3;
    for(int i=4;i<17;i++){
        t3.ajouter(i);
    }
    t3.inserer(1, 0);
    t3.inserer(0, 0);
    t3.inserer(3, 2);
    t3.inserer(2, 2);

    if(!(t1==t2)){
        std::cout << " ==> ECHEC #2" << std::endl;
        ok = false;
    }
    if(ok)
        std::cout << " ==> OK" << std::endl;
    return ok;
}

bool test10(){
    std::cout << "test10() : enlèvement" << std::endl;
    Dynamic_array<int> t1;
    for(int i=0;i<16;i++){
        t1.ajouter(i);
    }

    t1.enlever(5);
    Dynamic_array<int> t2;
    for(int i=0;i<5;i++){
        t2.ajouter(i);
    }
    for(int i=6;i<16;i++){
        t2.ajouter(i);
    }

    bool ok = true;
    if(!(t1==t2)){
        std::cout << " ==> ECHEC #2" << std::endl;
        ok = false;
    }
    if(ok)
        std::cout << " ==> OK" << std::endl;
    return ok;
}

bool test11(){
    std::cout << "test11() : chercher" << std::endl;
    Dynamic_array<int> t1;
    for(int i=0;i<100;i++){
        t1.ajouter(i*2);
    }

    bool ok = true;

    for(int i=0;i<100;i++){
        int index = t1.chercher(i*2);
        if(index != i){
            std::cout << " ==> ECHEC i=" << i << std::endl;
            ok = false;
            break;
        }
        index = t1.chercher(i*2+1);
        if(index != -1){
            std::cout << " ==> ECHEC i=" << i << std::endl;
            ok = false;
            break;
        }
    }
    if(ok)
        std::cout << " ==> OK" << std::endl;
    return ok;
}

class Point{
public:
    Point(double x_=0, double y_=0) : x(x_), y(y_){}
    bool operator == (const Point& autre) const{ return x==autre.x && y==autre.y;}
    bool operator<(const Point& autre) const;
private:
    double x, y;
};

bool Point::operator<(const Point& autre) const{
    if(x < autre.x) return true;
    if(x > autre.x) return false;
    return y < autre.y;
}

bool test12(){
    std::cout << "test12() : chercher" << std::endl;
    Dynamic_array<Point> points;
    points.ajouter(Point());
    points.ajouter(Point(2,3));
    points.ajouter(Point(4,5));
    points.ajouter(Point(3, 4));
    Dynamic_array<Point> points2;
    points2 = points;
    int index = points.chercher(Point(4,5));
    bool ok = index==2;
    if(ok)
        std::cout << " ==> OK" << std::endl;
    else
        std::cout << " ==> ECHEC" << std::endl;
    return ok;
}

int main(){
    bool testsreussis =
            true // Cette ligne «true» a été insérée pour facilier la mise en commentaire de la ligne suivante.
            && test1()
            && test2()
            && test3()
            && test4()
            && test5()
            && test6()
            && test7()
            && test8()
            && test9()
            && test10()
            && test11()
            && test12()
    ;

    std::cout << std::endl << std::endl
              << "**** Sommaire ****" << std::endl;

    if(testsreussis){
        std::cout << "=> BRAVO, tous les tests Lab3 ont été réussis!" << std::endl
                  << "=> Attention, ces tests ne sont pas exhaustifs." << std::endl
                  << "=> Réussir tous ces tests ne garanti l'absence de failles." << std::endl
                  << "=> Soyez vigilants, il pourrait rester des bogues." << std::endl;
    }else{
        std::cout << "=> DÉSOLÉ, au moins un test a échoué." << std::endl;
        std::cout << "=> Ne lâchez pas!" << std::endl;
    }
    return testsreussis ? 0 : 1;
}

