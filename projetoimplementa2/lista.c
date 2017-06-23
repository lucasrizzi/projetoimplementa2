#include <stdlib.h>
#include <stdio.h>
#include <lista_privado.h>

lista_t *lista_cria(void (*imp)(const void *), void (*libera)(void *), int (*comparar)(const void *, const void *),void(*salva)(const void*,FILE*)){
    lista_t  *novalista;
   	novalista=(lista_t*)malloc(sizeof(lista_t));
   	if (novalista==NULL){
    		return NULL;
    }
	novalista->tamanho=0;
	novalista->imprime=imp;
	novalista->destruir=libera;
	novalista->compara=comparar;
    novalista->cauda= NULL;
	novalista->cabeca= NULL;
	novalista->current=NULL;
	novalista->salvar=salva;
    	return novalista;
}

void lista_destroi(lista_t **l){
        	if(l==NULL){
	return;
   	 }
	void *aux;
	lista_t *auxiliar=*l;
	aux= NULL;
    	while(lista_remove((*l),(*l)->cabeca,&aux)){
    	if ((*l)->destruir!=NULL&&aux!=NULL){
    		(*l)->destruir(aux);
   	}
    	}
        free(*l);
        *l=NULL;
    }

int lista_vazia(lista_t *l){
    	if(l==NULL){
    	     return -1;
    	}
    	if(lista_tamanho(l)){
    	    return 0;
    	}
 	return 1;
}

int lista_tamanho(lista_t *l){
    	if(l==NULL){
    	    return -1;
    	}
	return l->tamanho;
}

celula_t *lista_cabeca(lista_t *l){
    	if(l==NULL){
   	    return NULL;
	}
    	return l->cabeca;
    }
celula_t *lista_cauda(lista_t *l){
    	if(l==NULL){
   	    return NULL;
	}
    	return l->cauda;
    }
void *lista_dado(celula_t *c){
    	if(c==NULL){
	        return NULL;
	    }
        return c->dado;
    }
celula_t *lista_proximo(celula_t *c){
    if(c==NULL){
	    return NULL;
	}
    	return c->prox;
    }
celula_t *lista_anterior(celula_t *c){
   	if(c==NULL){
	return NULL;
	}
   	return c->ant;
   }
int lista_eh_cabeca(lista_t *l, celula_t *c){
	if(l==NULL){
   	    return 0;
	}
	if(lista_vazia(l)){
	return 0;
	}
	if(c==NULL){
	return 0;
	}
   	if(c==l->cabeca){
   	return 1;
   	}
   	return 0;
   }
int lista_eh_cauda(lista_t *l, celula_t *c){
   	if(l==NULL){
   	    return 0;
	}
	if(lista_vazia(l)){
	return 0;
	}
	if(c==NULL){
	return 0;
	}
   	if(c==l->cauda){
   	return 1;
   	}
   	return 0;
   }
void lista_imprime(lista_t *l){
	if(l==NULL){
   	return ;
	}
	if(l->imprime==NULL){
	return ;
	}
   	celula_t *cel;
	cel=l->cabeca;
   	while (1){//desejo pela reprovacao
	if (cel==NULL){
	return ;}
   	l->imprime(cel->dado);
   	cel=cel->prox;
   	}
   }

lista_t *lista_concatena_e_destroi(lista_t **l1, lista_t **l2){
   	if (l1==NULL){return NULL;
	}
	if(l2==NULL){return NULL;
	}
	if(lista_vazia(*l1)&&lista_vazia(*l2)){
	return NULL;
	}
	lista_t *novalista;
	novalista=(lista_t*)malloc(sizeof(lista_t));
	if(lista_vazia(*l1)){
	novalista->cabeca=(*l2)->cabeca;
	novalista->cauda=(*l2)->cauda;
	novalista->tamanho=(*l2)->tamanho;
	novalista->imprime=(*l2)->imprime;
	novalista->destruir=(*l2)->destruir;
	novalista->compara=(*l2)->compara;
	free(*l2);
	free(*l1);
	*l2=*l1=NULL;
	return novalista;
	}
	novalista->cabeca=(*l1)->cabeca;
	novalista->tamanho=(*l1)->tamanho+(*l2)->tamanho;
	novalista->imprime=(*l1)->imprime;
	novalista->destruir=(*l1)->destruir;
	novalista->compara=(*l1)->compara;
	(*l1)->cauda->prox=(*l2)->cabeca;
	if(lista_vazia(*l2)){
		novalista->cauda=(*l1)->cauda;
		free(*l2);
	free(*l1);
	*l2=*l1=NULL;
		return novalista;
	}
	(*l2)->cabeca->ant=(*l1)->cauda;
	novalista->cauda=(*l2)->cauda;
	free(*l2);
	free(*l1);
	*l2=*l1=NULL;
	return novalista;
  }
//----------------------------------------------------------------------------------
int lista_insere_proximo(lista_t *l, celula_t *c, const void *elem){
    if (l==NULL){
        	return 0;
    	}
   	 if (elem==NULL){
       		 return 0;
  	  }
   	  celula_t *novacelula;
   	  novacelula=(celula_t*)malloc(sizeof(celula_t));
    	  if(novacelula==NULL){
     	   return 0;
  	  }
   	 novacelula->dado=elem;
    	if (c==NULL){
        	novacelula->ant=NULL;
        	novacelula->prox=l->cabeca;
       		 l->cabeca=novacelula;
       		 l->tamanho=l->tamanho+1;
            if (lista_tamanho(l)==1){
		    novacelula->prox=NULL;
			l->cauda=novacelula;}
			else{l->cabeca->prox->ant=novacelula;}
        		return 1;
    	}
    	novacelula->prox=c->prox;
    	c->prox=novacelula;
    	novacelula->ant=c;
    	if(c==l->cauda){
    	    l->cauda=novacelula;
    	}
    	else{
    	    novacelula->prox->ant=novacelula;
    	}
    	l->tamanho=l->tamanho+1;
    	return 1;
}


int lista_insere_anterior(lista_t *l, celula_t *c, const void *elem){
   	if (l==NULL){
        		return 0;
    	}
   	 if (elem==NULL){
       		 return 0;
  	  }
	if (c==NULL){return lista_insere_proximo(l, c, elem);}
    if(c==l->cabeca){return lista_insere_proximo(l,NULL,elem);}
   	return lista_insere_proximo(l,c->ant,elem);
   }

int lista_insere_posicao(lista_t *l, const unsigned int posicao, const void *elem){
  	if (l==NULL){
        	return 0;
    	}
   	 if (elem==NULL){
       		 return 0;
  	  }
  	if(posicao>=lista_tamanho(l)){
   	return lista_insere_proximo(l,l->cauda,elem);
   	}
   	celula_t *cel;
	int i;
	cel=l->cabeca;
   	for(i=0;i<posicao;i++){
   		cel=cel->prox;
   		i++;
   	}
   	return lista_insere_anterior(l,cel, elem);
   }
//--------------------------------------------------------------

int lista_remove(lista_t *l, celula_t *c, void **elem){
    if (l==NULL){
        return 0;
    }
    if(c==NULL){
        return 0;
    }
    if(lista_vazia(l)){
        return 0;
    }
    *elem=c->dado;
    if(l->tamanho==1){
        l->cauda=NULL;
        l->cabeca=NULL;
        free(c);
        c=NULL;
        l->tamanho=l->tamanho-1;
        return 1;
    }
    if(c==l->cabeca){
        l->cabeca=l->cabeca->prox;
        l->cabeca->ant=NULL;
        l->tamanho=l->tamanho-1;
        free(c);
        c=NULL;
        return 1;
    }
    if(c==l->cauda){
        l->cauda=l->cauda->ant;
        l->cauda->prox=NULL;
        l->tamanho=l->tamanho-1;
        free(c);
        c=NULL;
        return 1;
    }
    c->ant->prox=c->prox;
    c->prox->ant=c->ant;
    free(c);
    c=NULL;
    l->tamanho=l->tamanho-1;
    return 1;
}

celula_t *lista_busca_recursiva(lista_t *l, const void *elem, celula_t *c){
	if(l==NULL){
		return NULL;
	}
	if(elem==NULL){
		return NULL;
	}
	if(c==NULL){
		return NULL;
	}
	if(lista_vazia(l)){
		return NULL;
	}
	if(c->dado==elem){
		return c;
	}
	if(c->prox==NULL){
		return NULL;
	}
	return lista_busca_recursiva(l, elem, c->prox);
   }

lista_t *lista_separa(lista_t *l,const void *elem){
   	if(l==NULL){
		return NULL;
	}
	if(elem==NULL){
		return NULL;
	}
	if(l->tamanho==0){
		return NULL;
	}
	int i;
   	celula_t*encontra_a_celula;
	encontra_a_celula=lista_busca_recursiva(l, elem, l->cabeca);
   	if (encontra_a_celula==NULL){
   		return NULL;
  	}
  	lista_t *lista;
	lista=lista_cria(l->imprime, l->destruir, l->compara,l->salvar);
   	lista->cabeca=encontra_a_celula->prox;
   	lista->cauda=l->cauda;
   	l->cauda=encontra_a_celula;

   	lista->cabeca->ant=NULL;
   	for(i=0;encontra_a_celula!=lista->cauda;i++){
		encontra_a_celula=encontra_a_celula->prox;}
    l->cauda->prox=NULL;
	lista->tamanho=i;
	l->tamanho=l->tamanho-i;
   	return lista;
   }

//--------------------------------------------------------------
   int lista_insere_ordenado(lista_t *l, const void *elem){
   	if(l==NULL){
		return 0;
	}
	if(elem==NULL){
		return 0;
	}
	if(l->tamanho==0){
		return  lista_insere_proximo(l,NULL,elem);}
   	if(l->compara==NULL){
   		return  lista_insere_proximo(l,l->cauda,elem);
   	}
	celula_t* cel;
	cel=l->cabeca;
	while(l->compara(cel->dado,elem)<=0){
		cel=cel->prox;
		if(cel==NULL){
			return lista_insere_proximo(l,l->cauda,elem);
		}
	}
	return lista_insere_proximo(l,cel->ant,elem);
   }

   void imprime_linha(lista_t *buffer){
        if(buffer->current==NULL){
            buffer->imprime(buffer->cabeca->dado);
            buffer->current=buffer->cabeca;
            return;
        }
        buffer->imprime(buffer->current->dado);
   }

void lista_salva(lista_t *l,FILE *arquivo){
	if(l==NULL){
   	return ;
	}
	if(l->imprime==NULL){
	return ;
	}
   	celula_t *cel;
	cel=l->cabeca;
   	while (1){//desejo pela reprovacao
	if (cel==NULL){
	return ;}
   	l->salvar(cel->dado,arquivo);
   	cel=cel->prox;
   	}
   }


   void altera_current (lista_t *buffer,celula_t* posicao){
        buffer->current=posicao;
   }

   celula_t *retorna_current(lista_t *buffer){
    if (lista_vazia(buffer)){
        return NULL;
    }
    return buffer->current;
}

   celula_t *retorna_current_anterior(lista_t *buffer){
    if (lista_vazia(buffer)){
        return NULL;
    }
    return buffer->current->ant;
}

   celula_t *retorna_current_proximo(lista_t *buffer){
    if (lista_vazia(buffer)){
        return NULL;
    }
    return buffer->current->prox;
}

void pequeno_altera_current(lista_t *buffer,int praonde){
    if(lista_vazia(buffer)){
        return;
    }
    if(praonde){
        if(buffer->current->prox)
         buffer->current=buffer->current->prox;
        return;
    }
    if(buffer->current->ant)
        buffer->current=buffer->current->ant;
}

void current_linha_especifica(lista_t*buffer ,int posicao){
    if (lista_vazia(buffer))
        return;
    if(posicao>lista_tamanho(buffer))
        return;
    int i;
    buffer->current=buffer->cabeca;
    for(i=1;i<posicao;i++){
        buffer->current=buffer->current->prox;
    }
}

