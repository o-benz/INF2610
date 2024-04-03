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
	//TODO
}

void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
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
