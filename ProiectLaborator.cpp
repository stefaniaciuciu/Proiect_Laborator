#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

//Clasa abstracta pentru scrisoare
class Scrisoare
{
private:
    string Nume;
    string Prenume;
    int Varsta;
    string Oras; //Orase: Mažeikiai,Klaipėda,Kaunas,Vilnius
    string Culoare; // roz = fata; albastru = baiat
    int Nr; //Nr de dorinte ale fiecarui copil;
    string Dorinte[10]; //Am considerat ca fiecare copil vrea maxim 10 cadouri

public:
    virtual int GetCuminte()=0;


    Scrisoare(string nume, string prenume, int varsta, string oras, string culoare, string dorinte[10],int nr)
    {
        this->Nume = nume;
        this->Prenume = prenume;
        this->Varsta = varsta;
        this->Oras = oras;
        this->Culoare = culoare;
        this->Nr = nr;
        for(int i = 0; i < nr; i++)
            this->Dorinte[i] = dorinte[i];
    }
    string GetNume()
    {
        return this->Nume;
    }
    string GetPrenume()
    {
        return this->Prenume;
    }
    int GetVarsta()
    {
        return this->Varsta;
    }
    string GetOras()
    {
        return this->Oras;
    }
    string GetCuloare()
    {
        return this->Culoare;
    }
    int GetNr()
    {
        return this->Nr;
    }
    void GetDorinte(string dorinte[10])
    {
        for(int i = 0; i < this->Nr; i++)
            dorinte[i] = this->Dorinte[i];
    }
};

//Clasa pentru copiii cuminti
class ScrisoareNice : public Scrisoare
{
private:
    int Cuminte; //0 - copilul nu a fost cuminte, iar daca = 1 copilul a fost cuminte;

public:
    ScrisoareNice(string nume, string prenume, int varsta, string oras, string culoare, string dorinte[10],int nr) :Scrisoare(nume,prenume,varsta,oras,culoare,dorinte,nr)
    {
        Cuminte =1;
    }
    int GetCuminte()
    {
        return this->Cuminte;
    }
    ~ScrisoareNice() {};
};

//Clasa pentru copiii care nu au fost cuminti
class ScrisoareNaughty : public Scrisoare
{
private:

    int Cuminte; //0 - copilul nu a fost cuminte, iar daca = 1 copilul a fost cuminte;


public:
    ScrisoareNaughty(string nume, string prenume, int varsta, string oras, string culoare, string dorinte[10],int nr) : Scrisoare(nume, prenume, varsta, oras, culoare, dorinte, nr)
    {
        Cuminte=0;
    }

    int GetCuminte()
    {
        return this->Cuminte;
    }
    ~ScrisoareNaughty() {};
};

class Elfi
{
private:
    int Nr_acadele;
    int Nr_cadouri;
    string Cadouri[10];
    string Orase[10];
    int Nr_orase;
    int Nr_TotalacadeleNaughty;
    int Nr_TotalacadeleNice;

public:
    int GetNr_acadele()
    {
        return Nr_acadele;
    }
    int GetNr_cadouri()
    {
        return Nr_cadouri;
    }
    void GetCadouri(string cadouri[10])
    {
        for(int i = 0; i < Nr_cadouri; i++)
            cadouri[i] = Cadouri[i];
    }

    int GetNr_orase()
    {
        return Nr_orase;
    }
    void GetOrase(string orase[10])
    {
        for(int i = 0; i < Nr_orase; i++)
            orase[i] = this->Orase[i];
    }
    Elfi(string cadouri[10],int nr_acadele,int nr_cadouri,string orase[10], int nr_orase);
    ~Elfi() {};
    void CADOURI(list<ScrisoareNice> scrisoriNice, int *nr_fete1);
    void CADOURI(list<ScrisoareNaughty> scrisoriNaughty, int *nr_fete0);
    friend class Troli;
    friend class Doamna_Craciun;
    friend class Mos_Craciun;
};
Elfi::Elfi(string cadouri[10], int nr_acadele, int nr_cadouri, string orase[10], int nr_orase)
{
    this->Nr_acadele = nr_acadele;
    this->Nr_cadouri = nr_cadouri;
    for(int i = 0; i < this->Nr_cadouri; i++)
    {
        this->Cadouri[i] = cadouri[i];
    }
    this->Nr_orase = nr_orase;
    for(int i = 0; i < nr_orase; i++)
    {
        this->Orase[i] = orase[i];
    }

}

void AtelierElfi(string Obiecte_Atelier[10], int Pret[10])
{
    //Obiectele pe care elfii le au in atelier si pretul lor;
    Obiecte_Atelier[0] = "masinuta";
    Pret[0] = 30;
    Obiecte_Atelier[1] = "carte";
    Pret[1] = 50;
    Obiecte_Atelier[2] = "papusa";
    Pret[2] = 150;
    Obiecte_Atelier[3] = "ursulet";
    Pret[3] = 25;
    Obiecte_Atelier[4] = "minge";
    Pret[4] = 10;
    Obiecte_Atelier[5] = "trenulet";
    Pret[5] = 100;
    Obiecte_Atelier[6] = "stilou";
    Pret[6] = 8;
}
void Elfi::CADOURI(list<ScrisoareNice>  scrisori, int *nr_fete)
{
    this->Nr_TotalacadeleNice = 0;
    string Default = "trenulet"; //Cadoul default pentru copiii cuminti, in valoare de 100$;
    int S = 100; //Suma alocata cadourilor pentru copiii cuminti;
    *nr_fete = 0;

    //Obiectele pe care elfii le au in atelier si pretul lor;
    int Pret[10];
    string Obiecte_Atelier[10];
    AtelierElfi(Obiecte_Atelier,Pret);

    int k = 0;
    list <ScrisoareNice> :: iterator it;
    for(it = scrisori.begin(); it != scrisori.end(); ++it)
    {
        int Suma = 0;
        string dorinte[10];
        it->GetDorinte(dorinte);
        this->Nr_cadouri = 0;
        this->Nr_acadele = 0;
        for(int i = 0; i < it->GetNr(); i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(dorinte[i] == Obiecte_Atelier[j])
                {
                    Suma = Suma + Pret[j];
                    if(Suma <= S)
                    {
                        this->Cadouri[Nr_cadouri++] = Obiecte_Atelier[j];
                    }
                    if(Suma > S && i > 0 && this->Cadouri[0] != Default)
                    {
                        Suma = Suma - Pret[j];
                        this->Nr_acadele = S - Suma;
                    }

                    if(Suma > S && i == 0)
                    {
                        this->Cadouri[0] = Default;
                        this->Nr_cadouri = 1;
                        break;
                    }
                }
            }
        }
        cout<<"----------------------------------------------"<<endl;
        cout<<"Punga de cadouri pentru: "<<endl;
        cout<<"Nume: "<<it->GetNume()<<endl;
        cout<<"Prenume: "<<it->GetPrenume()<<endl;
        cout<<"Varsta: "<<it->GetVarsta()<<endl;
        cout<<"Oras: "<<it->GetOras()<<endl;
        //Verificam daca orasul se afla deja in lista
        //si daca acesta nu se afla in vector il adaugam;
        int o = 1;
        for( int i = 0; i < this->Nr_orase; i++)
            if(it->GetOras() == this->Orase[i])
                o = 0;
        if(o == 1)
        {
            this->Orase[Nr_orase] = it->GetOras();
            Nr_orase++;
        }
        cout<<"Culoare: "<<it->GetCuloare()<<endl;
        if(it->GetCuloare() == "roz") (*nr_fete)++;
        cout<<endl;
        cout<<"Contine urmatoarele: "<<endl;
        cout<<"Cadouri: ";

        for(int i = 0; i < this->Nr_cadouri; i++)
        {
            cout<<this->Cadouri[i]<<" ";
        }
        cout<<endl;
        this->Nr_TotalacadeleNice = this->Nr_TotalacadeleNice + Nr_acadele;
        cout<<"Nr acadele: "<<this->Nr_acadele<<endl;
        cout<<"----------------------------------------------"<<endl;
    }
}
void Elfi::CADOURI(list<ScrisoareNaughty> scrisori, int *nr_fete)
{
    this->Nr_TotalacadeleNaughty = 0;
    string Default = "minge"; //Cadoul default pentru copiii cuminti, in valoare de 10$;
    int S = 10; //Suma alocata cadourilor pentru copiii care nu au fost cuminti;
    int Pret[10];
    //int n = 0;//folosim pentru vectorul de stringuri pentru a stoca orasele;
    string Obiecte_Atelier[10];
    AtelierElfi(Obiecte_Atelier,Pret);
    (*nr_fete) = 0;
    list <ScrisoareNaughty> :: iterator it;
    for(it = scrisori.begin(); it != scrisori.end(); ++it)
    {
        this->Nr_cadouri = 0;
        this->Nr_acadele = 0;
        string dorinte[10];
        int Suma = 0;
        it->GetDorinte(dorinte);

        for(int i = 0; i < it->GetNr(); i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(dorinte[i] == Obiecte_Atelier[j])
                {
                    Suma = Suma + Pret[j];
                    if(Suma <= S)
                    {
                        this->Cadouri[Nr_cadouri++] = Obiecte_Atelier[j];
                    }
                    if(Suma > S && i > 0 && this->Cadouri[0] != Default)
                    {
                        Suma = Suma - Pret[j];
                        this->Nr_acadele = S - Suma;
                    }

                    if(Suma > S && i == 0)
                    {
                        this->Cadouri[0] = Default;
                        this->Nr_cadouri = 1;
                        break;
                    }
                }
            }
        }

        cout<<"----------------------------------------------"<<endl;
        cout<<"Punga de cadouri pentru: "<<endl;
        cout<<"Nume: "<<it->GetNume()<<endl;
        cout<<"Prenume: "<<it->GetPrenume()<<endl;
        cout<<"Varsta: "<<it->GetVarsta()<<endl;
        cout<<"Oras: "<<it->GetOras()<<endl;
        //Verificam daca orasul se afla deja in lista
        //si daca acesta nu se afla in lista il adaugam;
        int o = 1;
        for( int i = 0; i < this->Nr_orase; i++)
            if(it->GetOras() == this->Orase[i])
                o = 0;
        if(o == 1)
        {
            Orase[Nr_orase] = it->GetOras();
            Nr_orase++;
        }

        cout<<"Culoare: "<<it->GetCuloare()<<endl;
        if(it->GetCuloare() == "roz") (*nr_fete)++;
        cout<<"Contine urmatoarele: "<<endl;
        cout<<"Cadouri: ";
        for(int i = 0; i < this->Nr_cadouri; i++)
        {
            cout<<this->Cadouri[i]<<" ";
        }
        cout<<endl;
        this->Nr_TotalacadeleNaughty = this->Nr_TotalacadeleNaughty + Nr_acadele;
        cout<<"Nr acadele: "<<this->Nr_acadele<<endl;
        cout<<"----------------------------------------------"<<endl;
    }
}

class Troli
{
private:
    int AmbalajFete;
    int AmbalajBaieti;
    int Nr_carbuni;
public:
    Troli(int AmbalajF, int AmbalajB, int Nr_c)
    {
        this->AmbalajFete = AmbalajF;
        this->AmbalajBaieti = AmbalajB;
        this->Nr_carbuni = Nr_c;
    }
    ~Troli() {};
    friend class Elfi;
    friend class Doamna_Craciun;
    void Ambalaje()
    {
        cout<<"Nr ambalaje folosite pentru fete: "<<AmbalajFete<<endl;
        cout<<"Nr ambalaje folosite pentru baieti: "<<AmbalajBaieti<<endl;
    }
};

class Doamna_Craciun
{
private:
    float Buget_extra;
    int NrCarbuni;
    int NrAcadele;
public:
    int GetNrCarbuni()
    {
        return this->NrCarbuni;
    }
    int GetNrAcadele()
    {
        return this->NrAcadele;
    }
    float GetBuget()
    {
        return this->Buget_extra;
    }
    friend class Troli;
    friend class Elfi;
    friend void Afisare(float buget);
    void Buget(Elfi e, Troli t)
    {
        this->NrCarbuni = t.Nr_carbuni;
        this->NrAcadele = e.Nr_TotalacadeleNice + e.Nr_TotalacadeleNaughty;
        this->Buget_extra = t.Nr_carbuni*0.5+ this->NrAcadele;
    }
};

class Mos_Craciun
{
private:
    int Distanta;
    int Ruta[10];
    int nrOrase;
public:
    Mos_Craciun(int d, int r[10], int nrorase)
    {
        this->Distanta = d;
        this->nrOrase = nrorase;
        for(int i = 0; i < nrOrase; i++)
        {
            this->Ruta[i] = r[i];
        }
    }
    int GetnrOrase()
    {
        return this->nrOrase;
    }
    int GetDistanta()
    {
        return this->Distanta;
    }
    void GetRuta(int r[10])
    {
        for(int i = 0; i < this->nrOrase; i++)
            r[i] = this->Ruta[i];
    }
    friend class Doamna_Craciun; //Acum Doamna Craciun are acces la ruta lui Mos Craciun
    void Calcul_Ruta(Elfi e);
};

void bkt(int pos, int ad[5][5],bool vis[], int trMin[5],int tr[],int n, int lg, int &lgMin)
{
    if (lg >= lgMin)
        return;

    if (pos == n )
    {
        if (lg < lgMin)
        {
            lgMin = lg;
            for (int i = 0; i < n; i++)
                trMin[i] = tr[i];
        }
        return;
    }

    for (int i = 1; i < n; i++)
        if (!vis[i] && ad[tr[pos - 1]][i])
        {
            vis[tr[pos] = i] = true;
            lg += ad[tr[pos - 1]][i];
            bkt(pos + 1, ad,vis,trMin,tr,n,lg,lgMin);
            vis[i] = false;
            lg -= ad[tr[pos - 1]][i];
        }
}

//Orase: Mažeikiai,Klaipėda,Kaunas,Vilnius
void Mos_Craciun::Calcul_Ruta(Elfi e)
{
    string orase[10];
    e.GetOrase(orase); //preluam lista cu orase de la Elfi
    int nr = e.GetNr_orase(); //preluam nr de orase de la Elfi
    //Ordinea in care am pus orasele in graf:
    cout<<"0 - Rovaniemi"<<endl; //Rovaniemi este punctul de plecare => nodul 0;
    cout<<"1 - Kaunas"<<endl;
    cout<<"2 - Vilnius"<<endl;
    cout<<"3 - Mazeikiai"<<endl;
    cout<<"4 - Klaipeda"<<endl;
    int graph[5][5] = { { 0, 1294, 1313, 1152,1223 },
        { 1294, 0,89,183, 199 },
        { 1313, 89, 0, 256,286 },
        { 1152,183,256,0,95},
        { 1223,199, 286, 95, 0 }
    };
    int s = 0;
    int lgMin = 1000000;
    int trMin[5];
    int lg=0;
    int tr[5];
    bool vis[5]= {false, false, false, false,false };
    vis[tr[0] = 0] = true;
    bkt( 1, graph,vis,trMin,tr,5,lg,lgMin);
    cout<<endl;
    this->Distanta = lgMin;
    for(int i =0; i < 4; i++)
    {
        this->Ruta[i] = trMin[i];
    }
    cout<<"Ruta optima a  lui Mos Craciun: "<<endl;
    for(int i =0; i < 5; i++)
    {
        cout<<"--->"<<trMin[i]<<" ";
    }
    cout<<endl;
}
int Verificare(int cod[10])
{
    try
    {
        int v[4] = {1,4,5,3};
        int k = 0;
        for(int i = 0; i < 4; i++)
            if(v[i] == cod[i]) k++;
        if(k != 4)
            throw k;
    }
    catch(int j)
    {
        return 1;
    }
}
template <class T>

void Afisare(T distanta)
{
    cout<<"Distanta parcursa de Mos Craciun este: "<<distanta<<"km"<<endl;
}

template<>
void Afisare(float buget)
{
    cout<<"Bugetul extra calculat de Doamna Craciun este: "<<buget<<endl;
}

int main()
{

    list<ScrisoareNice> scrisoriNice;
    list<ScrisoareNaughty> scrisoriNaughty;
    list<Elfi> elfi;

    int nr1 = 0; //Numarul de copii cuminti;
    int nr0 = 0; //Numarul de copii care nu au fost cuminti ===== nr de carbuni folositi de Troli;

    string dorinte1[10] = {"masinuta","minge","pistol"};
    ScrisoareNice scrisoare1("Pop","Alexandru",6,"Vilnius","albastru",dorinte1,3);
    scrisoriNice.push_back(scrisoare1);
    nr1++;

    string dorinte2[10] = {"carte","minge","trenulet"};
    ScrisoareNice scrisoare2("Coiculescu","Veronica",5,"Vilnius","roz",dorinte2,3);
    scrisoriNice.push_back(scrisoare2);
    nr1++;

    string dorinte3[10] = {"stilou","minge","masinuta"};
    ScrisoareNaughty scrisoare3("Ionescu","Andrei",8,"Kaunas","albastru",dorinte3,3);
    scrisoriNaughty.push_back(scrisoare3);
    nr0++;

    string dorinte4[10] = {"papusa","ursulet"};
    ScrisoareNice scrisoare4("Voiculescu","Daniela",6,"Mazeikiai","roz",dorinte4,2);
    scrisoriNice.push_back(scrisoare4);
    nr1++;

    string dorinte5[10] = {"masinuta","carte"};
    ScrisoareNice scrisoare5("Lica","Ariana",8,"Klaipeda","roz",dorinte5,2);
    scrisoriNice.push_back(scrisoare5);
    nr1++;

    string cadouri[10];
    int nr_acadele = 0;
    int nr_cadouri = 0;
    int nr_orase = 0;
    string orase[10];
    Elfi e(cadouri,nr_acadele,nr_cadouri,orase,nr_orase);
    elfi.push_back(e);
    int nr_fete0 = 0;
    int nr_fete1 = 0;
    int cod[4];
    cout<<"Pentru a vedea rezultatele programului introduceti codul de 4 cifre(separate prin spatiu): "<<endl;
    cout<<"(Codul este 1 4 5 3)"<<endl;
    for(int i = 0; i < 4; i++)
        cin>>cod[i];

    int verif = Verificare(cod);


    do
    {
        if(verif == 0)
        {
            //Polimorfism static: supraincarcarea are loc la compilare
            e.CADOURI(scrisoriNice,&nr_fete1);
            e.CADOURI(scrisoriNaughty,&nr_fete0);
            e.GetOrase(orase);
            int nr_baieti0 = nr0-nr_fete0;
            int nr_baieti1 = nr1-nr_fete1;

            Troli t(nr_fete0+nr_fete1,nr_baieti0+nr_baieti1,nr0); //initializam nr de ambalaje pentru fete si baieti cu 0 si numarul
            //de carbuni = n0 ->nr de copii care nu au fost cuminti
            t.Ambalaje();

            Doamna_Craciun DC;
            DC.Buget(e,t);
            Afisare<float>(DC.GetBuget());

            int dist = 0;
            int r[10];
            int nror = 4;
            Mos_Craciun MC(dist,r,nror);
            MC.Calcul_Ruta(e);
            MC.GetRuta(r);
            Afisare<int>(MC.GetDistanta());
            break;
        }
        else
        {
            cout<<"Cod de verificare gresit!"<<endl;
            cout<<"Reintroduceti codul: "<<endl;
            for(int i = 0; i < 4; i++)
                cin>>cod[i];
            verif = Verificare(cod);
        }

    }
    while(verif !=2 );
}
