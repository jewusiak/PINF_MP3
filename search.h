#ifndef PINF_MP3_SEARCH_H
#define PINF_MP3_SEARCH_H

#include <stdlib.h>

typedef struct{
    int *seq;
    int nr;
} sequence_t;

typedef struct{
    sequence_t *elem;
    int nr;
} sequence_db;

void add_to_seq(sequence_t *sequence, int next){
    sequence->nr++;
    if(sequence->nr==1)
        sequence->seq=malloc(sizeof(*sequence->seq));
    else
        sequence->seq= realloc(sequence->seq, sequence->nr*sizeof *sequence->seq);
    sequence->seq[sequence->nr-1]=next;
}

void add_to_db(sequence_db *seq_db, sequence_t *next){
    seq_db->nr++;
    if(seq_db->nr==1)
        seq_db->elem=malloc(sizeof(*seq_db->elem));
    else
        seq_db->elem= realloc(seq_db->elem, seq_db->nr*sizeof *seq_db->elem);
    seq_db->elem[seq_db->nr-1]=next;
}

sequence_t *search_paths

#endif //PINF_MP3_SEARCH_H
