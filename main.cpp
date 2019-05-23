#include <iostream>
#include <vector>

using namespace std;

template <typename T>
    class ILessThanGen
    {
      public :
        virtual ~ILessThanGen (void) {}
        virtual bool operator () (const T &, const T &) const = 0;

    }; // ILessThanGen

template <typename T>
typename vector<T>::iterator partitionnement (const typename vector<T>::iterator& first,
                                              const typename vector<T>::iterator& last,
                                              const ILessThanGen<T>& compar)

{
    bool isUp(true);
    typename vector<T>::iterator pivot = first;
    typename vector<T>::iterator courant = last;
    int incr(-1);
    pivot   = first;
    courant = last;
    incr    = -1;
    while (pivot != courant)
    {
        if ((!isUp && compar(*pivot, *courant))
                ||
            (isUp && compar( *courant, *pivot)))
        {

            swap (*pivot, *courant);
            swap (pivot, courant);
            isUp = !isUp;
            incr = -incr;
        }
        courant = courant + incr;
    }
    return pivot;

}

template <typename T>
void quickSort (const typename vector<T>::iterator& begin,
                const typename vector<T>::iterator& end,
                const ILessThanGen<T>& compar)
{
    if (begin < end)
    {
        typename vector<T>::iterator it = partitionnement (begin, end - 1, compar);

        quickSort (begin, it, compar);
        quickSort (it + 1, end, compar);
    }
}

class Pers
   {
       string   myNom;
       unsigned myAge;

     public :
       Pers (const string & Nom, unsigned Age)
           : myNom (Nom), myAge (Age) {}

       const string & getNom (void) const noexcept { return myNom; }
       unsigned       getAge (void) const noexcept { return myAge; }

   private :
       ostream & display (ostream & os)  const
       {
           return os << getAge () << " - " << getNom ();

       } // display()

     public :
       friend ostream & operator << (ostream & os, const Pers & p)
       {
           return p.display (os);

       }

   }; // Pers

class TriParNomDesc : public ILessThanGen<Pers>
{
public:
    virtual ~TriParNomDesc() {}
    virtual bool operator()(const Pers& p1, const Pers& p2) const
    {
        return p1.getNom()>= p2.getNom();
    }
};

class TriParAgeAsc : public ILessThanGen<Pers>
{
public:
    virtual ~TriParAgeAsc() {}
    virtual bool operator()(const Pers& p1, const Pers& p2) const
    {
        return p1.getAge() <= p2.getAge();
    }
};

void functorSort (void)
    {
        cout << "FunctorSort : \n";

        typedef vector <Pers> CVPers;

        CVPers vPers;

        vPers.push_back ( Pers ("Charlotte", 21));
        vPers.push_back ( Pers ("Alfred",    12));
        vPers.push_back ( Pers ("Jean",      42));
        vPers.push_back ( Pers ("Noemie",    11));
        vPers.push_back ( Pers ("Berthe",    99));
        vPers.push_back ( Pers ("Agathe",    29));
        vPers.push_back ( Pers ("Sylvain",   42));
        vPers.push_back ( Pers ("Pierre",    75));

        cout << "\nTri par age croissant\n\n";

        quickSort (vPers.begin (), vPers.end (), TriParAgeAsc ());

        for (const Pers & personne : vPers)
            cout << personne << '\n';

        cout << "\nTri par nom decroissant\n\n";

        quickSort (vPers.begin (), vPers.end (), TriParNomDesc ());

        for (const Pers & personne : vPers)
            cout << personne << '\n';

    } // functorSort()

int main()
{
    functorSort();
    return 0;
}
