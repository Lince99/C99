/*
 * Basso Nicola
 * aka Lince99
 */
/*
 * library that provide various function that read, write and manage xml files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

typedef struct XMLNODEATTR xmlNodeAttr;
struct XMLNODEATTR {
    char* attr; /* <tag attr> */
    char* attr_val; /* <tag attr="val"> */
};

typedef struct XMLNODE xmlNode;
struct XMLNODE {
    int is_comment; /* flag if equal to 1 this node is a simple comment */
    char* tag; /* <tag> */
    char* tag_value; /* <tag> val </tag> */
    xmlNodeAttr** attributes; /* <tag attr[0]="val" attr[1]="val"> </tag> */
    int n_attributes; /* number of tag childs */
    xmlNode** childs; /* <tag> <tag[0]> </tag[0]> </tag> */
    int n_childs; /* number of tag childs */
};

typedef struct XMLDOC xmlDoc;
struct XMLDOC {
    char* name; /* file name */
    char* content; /* all xml content copied into this var */
    xmlNode* root; /* first root tag */
};



/*
 * funzione che inizializza un attributo per un nodo
 */
xmlNodeAttr* init_nodeAttr() {
    xmlNodeAttr* node = NULL;

    node = (xmlNodeAttr*) malloc(sizeof(xmlNodeAttr));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc xmlNodeAttr!" ANSI_RESET "\n");
        return NULL;
    }
    node->attr = NULL;
    node->attr_val = NULL;

    return node;
}

/*
 * funzione che inizializza un nuovo nodo xml
 */
xmlNode* init_node() {
    xmlNode* node = NULL;

    node = (xmlNode*) malloc(sizeof(xmlNode));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc xmlNode!" ANSI_RESET "\n");
        return NULL;
    }
    node->is_comment = 0;
    node->tag = NULL;
    node->tag_value = NULL;
    node->attributes = NULL;
    node->n_attributes = 0;
    node->childs = NULL;
    node->n_childs = 0;

    return node;
}

/*
 * funzione che inizializza un nuovo nodo xml
 */
xmlDoc* init_doc() {
    xmlDoc* doc = NULL;

    doc = (xmlDoc*) malloc(sizeof(xmlDoc));
    if(doc == NULL) {
        printf(ANSI_RED "Error on alloc xmlDoc!" ANSI_RESET "\n");
        return NULL;
    }
    doc->name = NULL;
    doc->content = NULL;
    doc->root = NULL;

    return doc;
}

/*
 * procedura che libera la memoria
 * occupata dagli attributi del nodo passato come parametro
 */
void free_attributes(xmlNode* node) {

    if(node == NULL)
        return;
    if(node->attributes != NULL)
        free(node->attributes);

}

/*
 * procedura che libera la memoria
 * occupata da il nodo passato e tutti i suoi sottoalberi
 */
void free_node(xmlNode* node) {

    if(node == NULL)
        return;
    if(node->childs != NULL) {
        for(; node->n_childs > 0; node->n_childs--) {
            if(node->childs[node->n_childs-1] != NULL)
                free_node(node->childs[node->n_childs-1]);
        }
    }

    free(node);

}

/*
 * procedura che libera la memoria
 * completamente occupata dall'albero xml
 */
void free_xml(xmlDoc* doc) {

    if(doc == NULL)
        return;
    if(doc->root != NULL)
        free_node(doc->root);
    free(doc);

}

/*
 * semplice funzione di stampa di una riga di separazione
 */
void print_separator(char* sep, int max_width) {
    int i = 0;

    for(i = 0; i < (int)(max_width/strlen(sep)); i++)
        printf("%s", sep);
    printf("\n");

}

/*
 * stampa le proprieta' e il contenuto del file xml
 */
void print_doc(xmlDoc* doc) {
    int i = 0;
    int length = 0;
    int trace = 0;
    char* data = NULL;

    if(doc == NULL) {
        printf(ANSI_YELLOW "Void document!" ANSI_RESET "\n");
        return;
    }
    printf("File name = " ANSI_CYAN "\"%s\"" ANSI_RESET "\n", doc->name);
    //print colorized xml
    data = doc->content;
    length = strlen(data);
    /*
     * 0 = BLUE = tag
     * 1 = CYAN = tag_value
     * 2 = RED = attribute
     * 3 = MAGENTA == attribute_value
     * 4 = GREEN = comment
     * 5 = YELLOW = close tag
     * WHITE = uknown
     */
    for(; i < length; i++) {
        //open tag
        if(data[i] == '<' || (trace == 3 && data[i] == '>'))
            trace = 0;
        //comment
        if(data[i+1] == '!' && trace == 0)
            trace = 4;
        //attribute
        if(data[i] == ' ' && (trace == 0 || trace == 3))
            trace = 2;
        //attribute value
        if(data[i] == '=' && trace == 2)
            trace = 3;
        //close tag
        if(data[i-1] == '>')
            trace = 1;
        //stampa
        switch(trace) {
            case 0:
                printf(ANSI_BLUE);
                break;
            case 1:
                printf(ANSI_CYAN);
                break;
            case 2:
                printf(ANSI_RED);
                break;
            case 3:
                printf(ANSI_MAGENTA);
                break;
            case 4:
                printf(ANSI_GREEN);
                break;
            default:
                printf(ANSI_WHITE);
                break;
        }
        printf("%c", data[i]);
    }
    printf(ANSI_RESET "\n");

    printf("Tree structrure is: ");
    if(doc->root != NULL)
        printf(ANSI_CYAN "SAVED" ANSI_RESET "\n");
    else
        printf(ANSI_YELLOW "NOT SAVED" ANSI_RESET "\n");

}

/*
 * procedura che stampa il nodo, le sue proprieta' e i tag delle foglie
 */
void print_node(xmlNode* node) {
    int i = 0;

    if(node == NULL) {
        printf(ANSI_YELLOW "Void node!" ANSI_RESET "\n");
        return;
    }
    //stampa il tag corrente al centro
    for(; i < node->n_childs-1; i++)
        printf("  ");
    if(node->is_comment)
        printf(ANSI_ITALIC ANSI_MAGENTA "\"%s\"" ANSI_RESET "\n", node->tag);
    else {
        if(node->tag == NULL)
            printf(ANSI_BOLD ANSI_CYAN "ROOT" ANSI_RESET "\n");
        else
            printf(ANSI_BOLD ANSI_BLUE "\"%s\"" ANSI_RESET "\n", node->tag);
        if(node->n_attributes != 0) {
            printf(ANSI_BLUE);
            for(i = 0; i < node->n_attributes; i++)
                printf("%s = %s\t",
                       node->attributes[i]->attr,
                       node->attributes[i]->attr_val);
            printf("\n" ANSI_RESET);
        }
    }
    //se non ci sono foglie allora lo comunica
    if(node->n_childs == 0) {
        //printf(ANSI_CYAN "nil " ANSI_RESET "\n");
        return;
    }
    //se ci sono allora le stampa tutte
    for(i = 0; i < node->n_childs; i++) {
        if(node->childs[i] != NULL) {
            if(node->childs[i]->is_comment)
                printf(ANSI_MAGENTA);
            else
                printf(ANSI_CYAN);
            printf("\t\"%s\"\n", node->childs[i]->tag);
        }
        else
            printf(ANSI_CYAN " nil ");
    }
    printf(ANSI_RESET "\n");

}

/*
 * procedura di stampa formattata dell'intero albero xml
 */
void print_tree(xmlNode* root, int level) {
    int i = 0;

    if(root == NULL) {
        if(level == 0)
            printf(ANSI_YELLOW "Void tree!" ANSI_RESET "\n");
        return;
    }
    //se sono al livello 0 stampo il valore di root
    if(level == 0)
        print_node(root);
    //se la radice attuale ha piu' foglie allora ne stampa i valori
    else if(root->n_childs != 0){
        if(root->is_comment)
            printf(ANSI_ITALIC ANSI_MAGENTA "\"%s\"" ANSI_RESET "\n", root->tag);
        else {
            if(level == 0)
                printf(ANSI_CYAN "ROOT" ANSI_RESET "\n");
            else
                printf(ANSI_BLUE "%s\n", root->tag);
            if(root->n_attributes != 0) {
                printf("ATTRIBUTES:\t");
                for(i = 0; i < root->n_attributes; i++)
                    printf("%s = %s\t",
                           root->attributes[i]->attr,
                           root->attributes[i]->attr_val);
                printf(ANSI_RESET);
            }
        }
        for(i = 0; i < root->n_childs; i++) {
            if(root->childs[i] != NULL)
                printf(ANSI_CYAN "\"%s\"", root->childs[i]->tag);
            else
                printf(ANSI_CYAN "nil ");
        }
        printf(ANSI_RESET "\n");
    }
    ++level;
    //stampa ricorsiva delle foglie che diventano a loro volta radici
    for(i = 0; i < root->n_childs; i++) {
        if(root->n_childs != 0)
            print_tree(root->childs[i], level);
    }
    printf(ANSI_RESET "\n");
}

/*
 * procedura che stampa tutte le informazioni estratte sul documento xml
 */
void print_xml(xmlDoc* doc) {
    char* sep = "- ";

    print_separator(sep, 80);
    printf("\t\t\t\tDocument data:\n");
    //print_doc(doc);
    print_separator(sep, 80);
    printf("\t\t\t\tXML Tree Structure:\n");
    print_tree(doc->root, 0);
    print_separator(sep, 80);
}

/*
 * funzione che restituisce la stringa estratta dalla posizione start alla end
 */
char* substring(char* str, int start, int end) {
    char* new = NULL;
    int i = 0;

    if(start > end || str == NULL || end > strlen(str))
        return NULL;
    if(start == 0 && end == strlen(str))
        return str;
    new = (char*) malloc(sizeof(char)*(end-start+1));
    while(start < end) {
        new[i] = str[start];
        ++start;
        ++i;
    }
    new[i] = '\0';

    return new;
}

/*
 * rimuove dalla stringa gli spazi, tab e newline all'inizio e alla fine
 */
char* trim_string(char* str) {
    int i = 0;
    int start = 0;
    int end = strlen(str);

    if(str == NULL)
        return NULL;
    for(; i < strlen(str); i++) {
        if(str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
            ++start;
        else
            break;
    }
    for(i = strlen(str)-1; i > start; i--) {
        if(str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
            --end;
        else
            break;
    }
    str = substring(str, start, end);

    return str;
}

/*
 * rimuove dalla stringa gli spazi, tab e newline tra i tag
 */
char* trim_xml(char* str) {
    int i = 0;
    int j = 0;
    int out_tag = 0;
    int save = 1;
    char* copy = NULL;

    if(str == NULL || strlen(str) == 0)
        return NULL;
    copy = (char*) calloc(sizeof(char), strlen(str));
    for(i = 0; i < strlen(str); i++) {
        //se sono uscito dal tag allora controllo per gli spazi vuoti
        if(str[i] == '>')
            out_tag = 1;
        //altrimenti salvo normalmente tutti i caratteri
        if(str[i] == '<')
            out_tag = 0;
        //se sono fuori e incontro altri tag/valori li salvo
        if(out_tag) {
            if(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
                save = 0;
            else
                save = 1;
        }
        //se sono dentro un tag o sono un valore salvo i caratteri
        if(!out_tag || save) {
            copy[j] = str[i];
            j++;
        }
    }
    copy = (char*) realloc(copy, sizeof(char)*(j+1));
    copy[j] = '\0';

    return copy;
}

/*
 * funzione che cerca il carattere find
 * nella stringa data a partire da start
 * e ritorna -1 in caso non trovi il carattere
 */
int get_pos(char* data, int start, char find) {
    int lung = 0;

    if(data == NULL)
        return -1;
    lung = strlen(data);
    if(start >= lung)
        return -1;
    for(; start < lung; start++) {
        if(data[start] == find)
            return start;
    }

    return -1;
}

/*
 ° funzione che ritorna solamente la stringa del tag (no attributi)
 */
char* extract_tag(char* text, int dim) {
    char* out = NULL;
    int out_dim = 0;
    int i = 0;

    if(text == NULL || dim == 0)
        return NULL;
    for(; out_dim < dim; ++out_dim) {
        if(text[out_dim] == ' ')
            break;
    }
    if(out_dim == dim)
        return NULL;
    out = (char*) malloc(sizeof(char)*(out_dim+1));
    if(out == NULL)
        return NULL;
    for(; i < out_dim; ++i)
        out[i] = text[i];
    out[i] = '\0';

    return out;
}

/*
 * funzione che estrae da un tag i vari attributi
 */
xmlNodeAttr** extract_attributes(char* text, int dim, int* n_attr) {
    xmlNodeAttr** out = NULL;
    int i = 0;
    int j = 0;
    int n_at = 0;

    for(; i < dim; i++) {
        if(text[i] == ' ' && i < dim-1) {
            while(text[i] == ' ' || text[i] == '\t')
                i++;
            //ottiene la lunghezza dell'attributo
            while(i+j < dim && text[i+j] != '=')
                j++;
            if(n_at == 0)
                out = (xmlNodeAttr**) malloc(sizeof(xmlNodeAttr*));
            else
                out = (xmlNodeAttr**) realloc(out,
                                              sizeof(xmlNodeAttr*)*n_at);
            //salva l'attributo
            out[n_at] = init_nodeAttr();
            if(out == NULL)
                break;
            out[n_at]->attr = substring(text, i, i+j);
            //ottiene la lunghezza del valore dell'attributo
            i += j;
            j = 0;
            if(text[i] == '=')
                i++;
            while(i+j < dim && text[i+j] != ' ') {
                j++;
            }
            out[n_at]->attr_val = substring(text, i, i+j);
            //passa al successivo
            n_at++;
            i += j-1;
            j = 0;
        }
    }

    *n_attr = n_at;
    return out;
}

/*
 * salva tag e attributi della radice passata come node
 * e ritorna il nodo creato
 */
xmlNode* save_tag(char* data, int start, xmlNode* root) {
    xmlNode* node = NULL;
    char* text = NULL;
    char* tmp = NULL;
    char* start_cmt = "<!--";
    char* end_cmt = "-->";
    int i = 0;

    //controlli sui parametri
    if(start >= strlen(data)-1 || start < 0 || root == NULL)
        return root;
    //e inizializzo il nuovo nodo e la posizione dei caratteri
    node = init_node();
    i = start;

    //estrae il contenuto del tag portando il contatore a '>'
    for(; data[i] != '>' && i < strlen(data); i++);
    text = substring(data, start, i+1);
    text = trim_string(text);
    print_separator("- ", 80);
    printf("TAG = "ANSI_BOLD"\"%s\""ANSI_RESET"\n", text);
    //se il tag corrente e' un commento allora lo estrae
    if(strncmp(text, start_cmt, strlen(start_cmt)) == 0) {
        tmp = substring(text, strlen(start_cmt),
                         strlen(text)-strlen(end_cmt));
        tmp = trim_string(tmp);
        node->tag = tmp;
        node->is_comment = 1;

    }
    //altrimenti e' un tag aperto con possibili attributi
    else {
        tmp = substring(text, 1, strlen(text)-1);
        tmp = trim_string(tmp);
        //estrae il nome del tag con la relativa funzione
        node->tag = extract_tag(tmp, strlen(tmp));
        //estrae gli attributi con la relativa funzione
        node->attributes = extract_attributes(tmp,
                                              strlen(tmp),
                                              &(node->n_attributes));
        //estrae il valore del tag attuale
        start = i;
        i = get_pos(data, i, '<')-1;
        if(i == -2)
            return root;
        printf("i = %d (max = %ld)\n", i, strlen(data));
        node->tag_value = trim_string(substring(data, start, i));
    }
    printf("Extracted node:\n");
    print_node(node);

    //assegna il nodo appena creato come figlio di root passato per parametro
    //se questo e' il primo nodo allora alloca l'array di foglie
    if(root->n_childs == 0) {
        root->childs = (xmlNode**) malloc(sizeof(xmlNode*));
        root->n_childs = 1;
        root->childs[0] = node;
        printf(ANSI_CYAN "First son!\n" ANSI_RESET);
    }
    //altrimenti rialloca l'array e assegna node all'ultima posizione
    else {
        root->n_childs++;
        root->childs = (xmlNode**) malloc(sizeof(xmlNode*)*
                                          (root->n_childs));
        root->childs[root->n_childs-1] = node;
        printf(ANSI_CYAN "%d son!\n" ANSI_RESET, root->n_childs);
    }

    //ora mi trovo alla chiusura del tag o alla fine del valore del tag
    i++;
    if(i >= strlen(data)-1)
        return root;
    //TODO fix ricorsione nel passare al prossimo tag o a tag chiuso
    //se successivamente trovo un commento allora sara' fratello di node
    if(data[i] == '<' && data[i+1] == '!') {
        printf("Found new comment!\n");
        save_tag(data, i, root);
    }
    //se trovo un tag chiuso avanzo e quello successivo sara' fratello di node
    else if(data[i] == '<' && data[i+1] == '/') {
        printf("Found close tag!\n");
        i++;
        //printf("\t%d = %c\n", i, data[i]);
        for(; data[i] != '<' && i < strlen(data)-1; i++);
        //printf("\t%d = %c\n", i, data[i]);
        save_tag(data, i, root);
    }
    //altrimenti se trovo un nuovo tag questo sara' figlio di node
    else {
        printf("Found new tag!\n");
        save_tag(data, i, node);
    }

    return root;
}

/*
 * TODO check recursion on save_tag and comment add_node
 */
xmlNode* add_node(char* data) {
    xmlNode* root = NULL;

    root = init_node();
    data = trim_xml(data);
    root = save_tag(data, 0, root);
    return root;
}

/*
 * funzione che restituisce la struttura documento
 * con il nome del file salvato,
 * ogni carattere dell'xml (per elaborazioni successive su stringhe)
 * e la struttura ad albero partendo da root
 */
xmlDoc* read_xml(char* file_name, char* mode) {
    xmlDoc* xml = NULL;
    FILE* fp = NULL;
    long dim = 0;

    //apre il file seguendo mode come modalita'
    fp = fopen(file_name, mode);
    if(fp == NULL) {
        printf(ANSI_RED "Error on read %s file!" ANSI_RESET "\n", file_name);
        return NULL;
    }
    //alloca il documento
    xml = init_doc();
    //salva il nome del file
    xml->name = file_name;
    //ottiene la dimensione
    fseek(fp, 0, SEEK_END);
    dim = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(dim) {
        //e salva l'intero contenuto nella variabile della struttura
        xml->content = (char*) malloc(sizeof(char)*dim);
        if (xml->content != NULL) {
            if(!fread(xml->content, sizeof(char), dim, fp))
                printf(ANSI_RED "Error on save xml text into buffer!"
                       ANSI_RESET "\n");
        }
    }
    fclose(fp);
    //crea l'albero dei tag
    xml->root = add_node(xml->content);

    return xml;
}
