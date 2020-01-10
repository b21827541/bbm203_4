#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>


typedef struct tree3{
    void* node1;
    void* node2;
    void* node3;
    int childs;
    int data;
}tree3;

typedef struct tree2{
    void* node1;
    void* node2;
    int childs;
    int data;
}tree2;

typedef struct tree0{
    char* op;
    int childs;
    int data;
}tree0;

typedef struct tree1{
    void* node1;
    int childs;
    int data;
}tree1;

int Random(int lower, int upper){
    int num = (rand() %(upper - lower + 1)) + lower;
    return num;
}

void AddExpr3(tree3* n);

tree0* new_node0(int data){
    tree0 *new_node = (tree0*)malloc(sizeof(tree0));
    new_node->data = data;
    new_node->childs = 0;
    new_node->op = NULL;

    return new_node;
}

tree1* new_node1(int data, int childs){
    tree1 *new_node = (tree1*)malloc(sizeof(tree1));
    new_node->node1 = NULL;
    new_node->childs = childs;
    new_node->data = data;

    return new_node;
}

tree2* new_node2(int data, int childs){
    tree2 *new_node = (tree2*)malloc(sizeof(tree2));
    new_node->node1 = NULL;
    new_node->node2 = NULL;
    new_node->childs = childs;
    new_node->data = data;

    return new_node;
}

tree3* new_node3(int data, int childs){
    tree3 *new_node = (tree3*)malloc(sizeof(tree3));
    new_node->node1 = NULL;
    new_node->node2 = NULL;
    new_node->node3 = NULL;
    new_node->childs = childs;
    new_node->data = data;

    return new_node;
}

tree3* add_child3(tree3* n, int data, int rand) {
    if (rand == 2 && data == 3) {
        if ((struct tree3 *) (n->node1) == NULL)
            return (n->node1 = new_node3(data, 3));
    }
    if (rand == 1 && data == 3) {
        if((struct tree2*) (n->node1) == NULL)
            return (n->node1 = new_node2(data, 2));
    }
    if (rand == 0 && data == 3) {
        if((struct tree1*) (n->node1) == NULL)
            return (n->node1 = new_node1(data, 1));
    }

    if (rand == 2 && data == 3) {
        if((struct tree3*)(n->node3) == NULL)
           return (n->node3 = new_node3(data, 3));
    }
    if (rand == 1 && data == 3) {
        if((struct tree2*)(n->node3) == NULL)
            return (n->node3 = new_node2(data, 2));
    }
    if (rand == 0 && data == 3) {
        if((struct tree1*)(n->node3) == NULL)
            return (n->node3 = new_node1(data, 1));
    }

    if(data == 2){
        if((struct tree3*)(n->node1) == NULL)
            return (n->node1 = new_node3(data, 3));
        if((struct tree3*)(n->node3) == NULL)
            return (n->node3 = new_node3(data, 3));
    }

    if((struct tree1*)(n->node2) == NULL)
        return(n->node2 = new_node1(data, 1));
}

tree2* add_child2(tree2* n, int data, int rand) {
    if(data == 5)
        return(n->node1 = new_node1(data, 1));

    if (rand == 2)
        return (n->node2 = new_node3(data, 3));

    if (rand == 1)
        return (n->node2 = new_node2(data, 2));

    if (rand == 0)
        return (n->node2 = new_node1(data, 1));
}

tree1* add_child1(tree1* n, int data) { // tree1* idi
    return(n->node1 = new_node1(data, 1));
}

tree0* add_child0(tree1* n, int data) {
    return(n->node1 = new_node0(data));
}

char* file_to_string(char* path){
    FILE* file = fopen(path, "r");
    int length = 0;
    char* string = malloc(0);

    if (!file){
        printf("%s", "asd");
        return NULL;
    }
    int c = fgetc(file);

    while (c != EOF){
        length++;
        string = realloc(string, (length + 1) * sizeof(char));
        string[length-1] = (char) c;
        c = fgetc(file);
    }
    string[length] = '\0';

    fclose(file);
    return string;
}

char* RandomRelOp() {
    char* rel_op = file_to_string("rel_op");
    char* rel_op_rest = rel_op;
    char* line, *string;
    FILE *fp;
    int count_relop = 0;
    fp = fopen("rel_op", "r");
    int c = fgetc(fp);
    while (c != EOF) {
        if(c == '\n')
            count_relop++;
        c = fgetc(fp);
    }
    fclose(fp);
    int rand_relop = Random(0,count_relop-1);
    int i = 0;
    while ((line = strtok_r(rel_op_rest, "\r\n", &rel_op_rest))) {
        if (strcmp(line, "\r\n") == 0) {
            *(line + strlen(line) - 2) = '\0';
        }
        if(i == rand_relop)
            break;
        i++;
    }
    string = malloc(sizeof(line)+1);
    strcpy(string,line);
    return string;
}

char* RandomVar() {
    char* var = file_to_string("var");
    char* var_rest = var;
    char* line;
    char* string;
    FILE *fp;
    int count_var = 0;
    fp = fopen("var", "r");
    int c = fgetc(fp);
    while (c != EOF) {
        if(c == '\n')
            count_var++;
        c = fgetc(fp);
    }
    fclose(fp);
    int rand_var = Random(0,count_var-1);
    int i = 0;
    while ((line = strtok_r(var_rest, "\r\n", &var_rest))) {
        if (strcmp(line, "\r\n") == 0) {
            *(line + strlen(line) - 2) = '\0';
        }
        if(i == rand_var)
            break;
        i++;
    }
    string = malloc(sizeof(line)+1);
    strcpy(string,line);
    return string;
}

char* RandomPreOp() {
    char* pre_op = file_to_string("pre_op");
    char* pre_op_rest = pre_op;
    char* line,* string;
    FILE *fp;
    int count_pre_op = 0;
    fp = fopen("pre_op", "r");
    int c = fgetc(fp);
    while (c != EOF) {
        if(c == '\n')
            count_pre_op++;
        c = fgetc(fp);
    }
    fclose(fp);
    int rand_pre_op = Random(0,count_pre_op-1);
    int i = 0;
    while ((line = strtok_r(pre_op_rest, "\r\n", &pre_op_rest))) {
        if (strcmp(line, "\r\n") == 0) {
            *(line + strlen(line) - 2) = '\0';
        }
        if(i == rand_pre_op)
            break;
        i++;
    }
    string = malloc(sizeof(line)+1);
    strcpy(string,line);
    return string;
}

char* RandomOpOp() {
    char* op = file_to_string("op");
    char* op_rest = op;
    char* line, *string;
    FILE *fp;
    int count_op = 0;
    fp = fopen("op", "r");
    int c = fgetc(fp);
    while (c != EOF) {
        if(c == '\n')
            count_op++;
        c = fgetc(fp);
    }
    fclose(fp);
    int rand_op = Random(0,count_op-1);
    int i = 0;
    while ((line = strtok_r(op_rest, "\r\n", &op_rest))) {
        if (strcmp(line, "\r\n") == 0) {
            *(line + strlen(line) - 2) = '\0';
        }
        if(i == rand_op)
            break;
        i++;
    }
    string = malloc(sizeof(line)+1);
    strcpy(string,line);
    return string;
}

char* RandomSetOp() {
    char* set_op = file_to_string("set_op");
    char* set_op_rest = set_op;
    char* line;
    char* string;
    FILE *fp;
    int count_setop = 0;
    fp = fopen("set_op", "r");
    int c = fgetc(fp);
    while (c != EOF) {
        if(c == '\n')
            count_setop++;
        c = fgetc(fp);
    }
    fclose(fp);
    int rand_setop = Random(0,count_setop-1);
    int i = 0;
    while ((line = strtok_r(set_op_rest, "\r\n", &set_op_rest))) {
        if (strcmp(line, "\r\n") == 0) {
            *(line + strlen(line) - 2) = '\0';
        }
        if(i == rand_setop)
            break;
        i++;
    }

    string = malloc(sizeof(line)+1);
    strcpy(string,line);
    return string;
}

void AddOp(tree1* node){
    if(node->data == 7){
        node->node1 = add_child0(node, 77);
        ((struct tree0*)(node->node1))->op = RandomSetOp();
        printf("%s %s\n", "setop",((struct tree0*)(node->node1))->op);
    }
    if(node->data == 6){
        node->node1 = add_child0(node, 66);
        ((struct tree0*)(node->node1))->op = RandomRelOp();
        printf("%s %s\n", "relop",((struct tree0*)(node->node1))->op);
    }
    if(node->data == 8){
        node->node1 = add_child0(node,88);
        ((struct tree0*)(node->node1))->op = RandomVar();
        printf("%s %s\n", "var",((struct tree0*)(node->node1))->op);
    }
    if(node->data == 5){
        node->node1 = add_child0(node, 55);
        ((struct tree0*)(node->node1))->op = RandomPreOp();
        printf("%s %s\n", "preop",((struct tree0*)(node->node1))->op);
    }
    if(node->data == 4){
        node->node1 = add_child0(node, 44);
        ((struct tree0*)(node->node1))->op = RandomOpOp();
        printf("%s %s\n", "opop",((struct tree0*)(node->node1))->op);
    }
}

void AddExpr1(tree1* n) {
    n->node1 = add_child1(n,8); // 8 var
    AddOp(n->node1);
}

void AddExpr2(tree2* n) {
    int j;
    for(j = 1; j <= 2; j++){
        if(j == 1){
            n->node1 = add_child2(n, 5, 1); // 5 preop
            AddOp(n->node1);
        }
        if( j == 2) {
            int k = Random(0,2);
            n->node2 = add_child2(n,3,k);
            if(k == 0)
                AddExpr1(n->node2);
            if(k == 1)
                AddExpr2(n->node2);
            if(k == 2)
                AddExpr3(n->node2);
        }
    }
}

void AddExpr3(tree3* n){
    int j;
    for(j = 1; j <= 3; j++){
        if (j == 2) {
            n->node2 = add_child3(n, 4, 1); // 7 set op
            AddOp(n->node2);
        }
        if(j == 1){
            int l = Random(0,2);
            n->node1 = add_child3(n, 3, l);
            if(l == 0)
                AddExpr1((tree1*)n->node1);
            if(l == 1)
                AddExpr2((tree2*)n->node1);
            if(l == 2)
                AddExpr3((tree3*)n->node1);
        }
        if(j == 3){
            int k = Random(0,2);
            n->node3 = add_child3(n, 3, k);
            if(k == 0)
                AddExpr1((tree1*)n->node3);
            if(k == 1)
                AddExpr2((tree2*)n->node3);
            if(k == 2)
                AddExpr3((tree3*)n->node3);
        }
    }
}

void AddCond(tree3* node){
    int i = Random(0,1);
    int j;
    for ( j = 1; j <= 3; j++ ) {
        if (i == 0) {
            if (j == 2) {
                node->node2 = add_child3(node, 7, 1); // 7 set op
                AddOp(node->node2);
            }else if(j == 1){
                node->node1 = add_child3(node, 2, 3); // 2 cond
                AddCond(node->node1);
            }else{
                node->node3 = add_child3(node, 2, 3);
                AddCond(node->node3);
            }
        } else {
            if (j == 2) {
                node->node2 = add_child3(node, 6, 1); // 6 rel op
                AddOp((tree1*)(node->node2));
            }
            if(j == 1){
                int l = Random(0,2);
                node->node1 = add_child3(node, 3, l); // 3 expr
                if(l == 0)
                    AddExpr1((tree1*)(node->node1));
                if(l == 1)
                    AddExpr2((tree2*)(node->node1));
                if(l == 2)
                    AddExpr3((tree3*)(node->node1));
            }
            if(j == 3){
                int k = Random(0,2);
                node->node3 = add_child3(node,3,k);
                if(k == 0)
                    AddExpr1((tree1*)(node->node3));
                if(k == 1)
                    AddExpr2((tree2*)(node->node3));
                if(k == 2)
                    AddExpr3((tree3*)(node->node3));
            }
        }
    }
}

void Print(void* node){
    if(((struct tree0*)(((struct tree1*)node)->node1))->childs == 0){
        printf("%s",((struct tree0*)(((struct tree1*)node)->node1))->op);
    }

    if(node != NULL && ((struct tree3*)node)->childs == 3) {
        printf("%s", "(");

        if(((struct tree3*)(((struct tree3*)node)->node1))->childs == 3)
            Print((struct tree3*)((struct tree3*)node)->node1);
        else if(((struct tree2*)(((struct tree3*)node)->node1))->childs == 2)
            Print((struct tree2*)((struct tree3*)node)->node1);
        else if(((struct tree1*)(((struct tree3*)node)->node1))->childs == 1)
            Print((struct tree1*)((struct tree3*)node)->node1);


        if(((struct tree1*)(((struct tree3*)node)->node2))->childs == 1)
            Print((struct tree1*)((struct tree3*)node)->node2);

        if(((struct tree3*)(((struct tree3*)node)->node3))->childs == 3)
            Print((struct tree3*)((struct tree3*)node)->node3);
        else if(((struct tree2*)(((struct tree3*)node)->node3))->childs == 2)
            Print((struct tree2*)((struct tree3*)node)->node3);
        else if(((struct tree1*)(((struct tree3*)node)->node3))->childs == 1)
            Print((struct tree1*)((struct tree3*)node)->node3);

        printf("%s", ")");
    }
    if(node != NULL && ((struct tree2*)node)->childs == 2) {

        if(((struct tree1*)(((struct tree2*)node)->node1))->childs == 1)
            Print((struct tree1*)((struct tree2*)node)->node1);

        if(((struct tree2*)node)->data == 3)
            printf("%s", "(");

        if(((struct tree3*)(((struct tree2*)node)->node2))->childs == 3)
            Print((struct tree3*)((struct tree2*)node)->node2);
        else if(((struct tree2*)(((struct tree2*)node)->node2))->childs == 2)
            Print((struct tree2*)((struct tree2*)node)->node2);
        else if(((struct tree1*)(((struct tree2*)node)->node2))->childs == 1)
            Print((struct tree1*)((struct tree2*)node)->node2);

        if(((struct tree2*)node)->data == 3)
            printf("%s", ")");
    }
    if(node != NULL && ((struct tree1*)node)->childs == 1) {
        if (((struct tree1 *) (((struct tree1 *) node)->node1))->childs == 1)
            Print((struct tree1 *) ((struct tree1 *) node)->node1);
    }
}

int main() {
    struct tree3* root = NULL;
    root = new_node3(2, 3);
    srand(time(0));
    AddCond(root);
    printf("%s %s", "if","(");
    Print(root);
    printf("%s", ")");
    return 0;
}