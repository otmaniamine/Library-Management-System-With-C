
# Library Management System With C

Système de gestion de bibliothèque avancé en C avec récupération automatisée des livres via robot de stockage.

##  Description

Application complète de gestion de bibliothèque permettant :
- Catalogage et indexation des livres
- Gestion des emprunts et retours
- **Récupération automatisée des livres** via machine de stockage intelligente
- Interface utilisateur intuitive

##  Fonctionnalités principales

### Gestion Classique
-  Ajout/suppression/modification de livres
-  Recherche par titre, auteur, ISBN, catégorie
-  Gestion des adhérents (lecteurs)
-  Suivi des emprunts et retours
-  Calcul automatique des amendes de retard
-  Réservation de livres
-  Génération de rapports

###  Système de Récupération Automatisée (NOUVEAU)
-  **Machine de stockage robotisée** intégrée
-  **Logiciel de commande** - Interface de recherche et commande
-  **Localisation automatique** des livres en stock
-  **Préparation automatisée** - La machine prépare le livre demandé
-  **Récupération sans effort** - Le livre arrive à la sortie de la machine
-  **Historique des commandes** et traçabilité
-  **Notifications** quand le livre est prêt à récupérer

##  Technologies utilisées

- **Langage** : C (C99 standard)
- **Structure de données** : Listes chaînées, arbres, files d'attente
- **Interface** : Ligne de commande (Terminal) / Menu interactif
- **Persistance** : Fichiers binaires/texte (CSV/JSON)
- **Communication** : Socket pour communication machine-logiciel



##  Guide d'utilisation

### Commande via Machine de Récupération

```
>>> Rechercher un livre
Titre : "Le Seigneur des Anneaux"

Résultats :
- ISBN : 978-2253045908
  Auteur : Tolkien
  Emplacement : Rack-C-12 (Machine)
  Disponible : ✅

>>> Ajouter au panier et commander
La machine localise automatiquement le livre...
Préparation en cours : ████████████ 87%
Livre prêt à récupérer au point de sortie !
```

### Workflow Emprunts Classiques

```
1. Chercher livre
2. Vérifier disponibilité
3. Emprunter (enregistrement automatique)
4. Retour avec calcul des amendes
```

## 📁 Structure du projet

```
Library-Management-System-With-C/
├── src/
│   ├── main.c                 # Point d'entrée
│   ├── book.c/h               # Gestion des livres
│   ├── member.c/h             # Gestion des adhérents
│   ├── loan.c/h               # Gestion des emprunts
│   ├── machine.c/h            # 🤖 Interface machine automatisée
│   ├── search.c/h             # Moteur de recherche
│   └── utils.c/h              # Utilitaires
├── data/
│   ├── books.csv              # Base de livres
│   ├── members.csv            # Base d'adhérents
│   └── loans.log              # Historique emprunts
└── docs/
    └── MACHINE_GUIDE.md       # Doc système automatisé
```

##  Intégration Machine

### Architecture du Système Automatisé
```
┌─────────────────────┐
│  Application C      │
│  (Gestion + Search) │
└──────────┬──────────┘
           │ Serial/TCP
           ↓
┌─────────────────────┐
│  Robot Stockage     │
│  (Préparation)      │
└──────────┬──────────┘
           │
           ↓
┌─────────────────────┐
│  Rack Automatisé    │
│  (Localisation)     │
└─────────────────────┘
```

### Commande Machine via Logiciel
```c
// Demander un livre via la machine
int deliver_book(char* isbn, int member_id) {
    send_to_machine(isbn);           // Envoyer à la machine
    wait_for_delivery();             // Attendre livraison
    log_transaction(member_id, isbn);// Enregistrer
    return SUCCESS;
}
```



##  Travaux Futurs (Roadmap)

### Phase 2
- [ ] Interface GUI (Qt/GTK)
- [ ] Support code-barres/RFID
- [ ] Authentification multi-utilisateurs
- [ ] **Notifications automatiques** SMS/Email

### Phase 3
- [ ] Application mobile (Android/iOS)
- [ ] Dashboard analytics en temps réel
- [ ] Système de recommandation intelligent





##  Avantages du Système Automatisé

 **Gain de temps** - Plus de recherche manuelle  
 **Gain d'espace** - Rangement optimisé  
 **Accessibilité** - Idéal pour personnes à mobilité réduite  
 **Disponibilité 24/7** - Machine accessible en continu  
 **Traçabilité** - Historique numérique complet  
 **Efficacité** - Gestion automatisée des stocks  

##  Licence

Licence MIT - Libre d'utilisation

