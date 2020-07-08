//
// Created by lsc on 20-07-08.
//

//#ifndef LSC_BOOK_H
//#define LSC_BOOK_H

#pragma once
#include <Lsc/AppBook/Lib.h>
#include <Lsc/Rem/Rem.h>
#include <memory>
#include <map>




namespace Lsc
{
/*
    BOOK (HTML)
       \  (Grandes Structures:)
        - Table des matières (...disons...) - Titre des "Topics" et le lien du "Topic" dans le livre.
                           \
                            - Titre de topic [ lien du topic dans le livre ]
                                           \
                                            - Sections ... [liens ... ]

        [- Legendes ( Code de couleurs; Par type d'entree; Par évenement, etc... )]
        
        - Topics [ Mechanisme de creation: Book::Topic::Create(...) ]
               \
                - Sections [ S = Topic.NewSection(Book::Topic*, "SectionName"); Book::Log& Log = S.Entry(...) ]
                         \
                          - Entrées (LOG) [ Ai-je besoin d'acceder à l'instance section-parent ici ? ]
        
        - Contenu Chronologique (Section) de toutes les entrées(Log).
        - ...
        
        
Données de Configuration: (Valeurs persistantes et spécifiques, stockées dans une base de données SQLite3 sous forme de fichier. )
                          Mais comme l'on peut constater, il ne faut pas se rerndre fou à essayer de correspondre et de corriger
                          l'ensemble des couleurs énumérées entre le web et X11/Console true color...
                          
Alors au besoin, seulement, nous allons adapter les cas particuliers une fois rendus "à la traversée du pont".........
 
 
    Le danger de vouloir refaire les donnees de references dans la DB ... Merde!
 
    [TABLE ColorNum]
    - ID  PRIMARY KEY AI
    - Code INTEGER UNIQUE ( static_cast<uint16_t>(Lsc::Color::*); ) ( Les couleurs EFFECTIVEMENT UTILISÉES )
    - Name              ( Name TEXT UNIQUE ) - Probablement le nom de la couleur enumeree sous Lsc::Color ... sinon la correction WEB/X11
      Donc l'on va insérer des donnees au fur et a mesure que l'on voudra associer une couleur a un item ...
    
    - Associer une ColorNum à un mode ( en l'occurence 'HTML' )
    [TABLE Mode] ... ? Whatever...
    - Name Text PRIMARY KEY  ( 'HTML'; 'ANSI'; 'CURSES/tui++']
    - RenderStart TEXT  ( en l'occurence: 'HTML'::'<span color**="ColorNum::Name">', 'ANSI'::'\033[38;5;%dm' )
    - RenderEnd   TEXT  ( en l'occurence: 'HTML'::'</span>', 'ANSI'::'\033[0m')
    - ... Whatever... // Pour le moment on reflechis tres fort pour les couleurs....
    
    ** Ou sinon class ="style de la classe" -- ou un style/classe implicite sous un conteneur CSS parent ... pffff!
    
    
    - ....
    
    // Nous ne sommes pas encore rendus au "styles" de texte html: ( <p>; <article>; <head> ...  <div class='...'> .... Pfff!
    

    
    
    Pour l'instance Book:
    
        Une single instance GLOBALE ( ouaip... Application Book c'est quoi à votre avis?? ^^ )
        
        
 */

/*!
 * @brief Application Book
 *
 * Si je veux ecrire une entree ( log ) dans une section effectivement :
 *  Soit
 *  @code
 *      Section::Debug() << ...;
 *  @endcode
 *  -> Section::Debug() créé une instance Book::Log de type DEBUG ( implicitement, ça tire la config du style debug ....)
 *      Et le mechanisme d'enchainement des appels de la surcharge de l'operateur '<<' adressé à l'instance Log cree par Section::Debug().
 *
 *      S = Book::SelectTopic("Nom du Topic").SelectSection("Nom de la Section);
 *      S.Debug() << "..." ;
 *      S.Info() << "..." ;
 *      S.XXX() << "...";
 *
 *      Donc la Table Des Matières devrait s'auto-générer ... ^^
 *      Ansi que les légendes..
 *
 *      Maintenant que l'on a une vue rapide et simple de l'ensemble de la structure du "Book",
 *      il faut elaborer l'adressage et le stockage des items de config et objets de contenu.
 *      Examples: <fin de ligne> <prefix de log > < gestion des indentations > < estampe horodatage > < paragraphe > < titre/section/article> < styles et couleurs - effectivement...>
 *
 */
class APPBOOK_LIB Book
{
public:
    class Topic;
    
    using Shared = std::shared_ptr<Book>;
    
    struct APPBOOK_LIB Log
    {
        // Donc j'ai pas besoin de lier une instance Log à quoi que ce soit... À voir ...
        using Collection = std::vector<Log>;
        using GlobalCollection = std::vector<Log *>;
        
    };
    
    class APPBOOK_LIB Section
    {
        String mName;
        Book::Topic* mTopic;
        
    public:
        // Ici non-plus je n'ai à lier une instance Section à une instance Topic --
        // Mais - Comme il n'y aura pas une tonne de sections, je devrais lier à l'instance de Topic parent.
        
        
        using Dictionary = std::map<std::string, Section *>;
        
    };

    class APPBOOK_LIB Topic
    {
        String mName;
        Book::Section::Dictionary mSections;
        
    public:
        using Dictionary = std::map<std::string, Topic*>;
        
    };
    
private:
    Book::Log::GlobalCollection mLogs; ///< Sous Réserve parceque les entrees sont stockees sous les topics/sections.
    Book::Topic::Dictionary     mTopics;
    
    
    
};

}

//#endif //LSC_BOOK_H
