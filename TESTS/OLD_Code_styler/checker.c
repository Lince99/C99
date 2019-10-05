/*
 * Basso Nicola
 * aka Lince99
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/colors.h"
#include "lib/xml_reader.h"



int main(int argc, char** argv) {
    xmlDoc* xml = NULL;

    //char file_name[] = "styles/example_style.xml";
    char file_name[] = "styles/small_example_style.xml";
    char mode[] = "r";
    //read xml recursively
    xml = read_xml(file_name, mode);
    //print a tree format for all content
    //print_xml(xml);
    /*do {
        if(data[i] == '<')
            i = save_tag(data, tmp_len, xml->root);
        i++;
    } while(i < len);*/

    free_xml(xml);

    return 0;
}
