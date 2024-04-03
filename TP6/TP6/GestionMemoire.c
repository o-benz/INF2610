#include "./libs/lib.h"

#define TAILLE_PAGE 1024

unsigned int calculerNumeroDePage(unsigned long adresse) {
    return adresse / TAILLE_PAGE;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
     return adresse % TAILLE_PAGE;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
     return numeroDePage * TAILLE_PAGE + deplacementDansLaPage;
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	unsigned int numeroPageRecherche = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned int deplacementDansLaPageRecherche = calculerDeplacementDansLaPage(req->adresseVirtuelle);
    req->estDansTLB = 0;
    req->adressePhysique = 0;

    for (int i = 0; i < TAILLE_TLB; i++) {
        if (mem->tlb->numeroPage[i] == numeroPageRecherche && mem->tlb->entreeValide[i]) {
            req->estDansTLB = 1;
            req->adressePhysique = calculerAdresseComplete(mem->tlb->numeroCadre[i], deplacementDansLaPageRecherche); 
            mem->tlb->dernierAcces[i] = req->date; 
            return; // Sortie anticipée dès qu'une correspondance est trouvée
        }
    }
	req->adressePhysique = 0;
}

void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	unsigned int numeroPageRecherche = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned int deplacementDansLaPageRecherche = calculerDeplacementDansLaPage(req->adresseVirtuelle);
    req->estDansTablePages = 0;
    req->adressePhysique = 0;

    for (unsigned int i = 0; i < TAILLE_TP; i++) {

        if (mem->memoire->numeroPage[i] == numeroPageRecherche && mem->tp->entreeValide[i]) {
            req->estDansTablePages = 1;
            req->adressePhysique = calculerAdresseComplete(mem->tlb->numeroCadre[i], deplacementDansLaPageRecherche); 
            return; // Sortie anticipée dès qu'une correspondance est trouvée
        }
    }
	req->adressePhysique = 0;

}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	unsigned int numeroDePage = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned long offsetAdresse = calculerDeplacementDansLaPage(req->adresseVirtuelle);

	for (unsigned int i = 0; i < TAILLE_MEMOIRE; i++)
	{
		if (!mem->memoire->utilisee[i])
		{
			req->adressePhysique = calculerAdresseComplete(i, offsetAdresse);

			mem->memoire->numeroPage[i] = numeroDePage;
			mem->memoire->dateCreation[i] = req->date;
			mem->memoire->dernierAcces[i] = req->date;
			mem->memoire->utilisee[i] = 1;

			return;
		}
	}
}

void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	int indiceRemplacement = 0;
	int numeroPage = calculerNumeroDePage(req->adresseVirtuelle);
	int numeroCadre = calculerNumeroDePage(req->adressePhysique);
	unsigned long plusAncienneDate = mem->tlb->dateCreation[numeroPage];

	for (int i = 0; i < TAILLE_TLB; i++)
	{
		if (mem->tlb->entreeValide[i])
		{
			if (mem->tlb->dateCreation[i] < plusAncienneDate)
			{
				plusAncienneDate = mem->tlb->dateCreation[i];
				indiceRemplacement = i;
			}
		}
		else
		{
			indiceRemplacement = i;
			break;
		}
	}
	mem->tlb->numeroPage[indiceRemplacement] = numeroPage;
	mem->tlb->numeroCadre[indiceRemplacement] = numeroCadre;
	mem->tlb->entreeValide[indiceRemplacement] = 1;
	mem->tlb->dernierAcces[indiceRemplacement] = req->date;
	mem->tlb->dateCreation[indiceRemplacement] = req->date;
}

// NE PAS MODIFIER
int main() {
    evaluate(
		&calculerNumeroDePage, 
		&calculerDeplacementDansLaPage, 
		&calculerAdresseComplete, 
        &rechercherTLB, 
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire
    );
    return 0;
}
