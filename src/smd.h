//
// smd.h
//
// Copyright (c) 1997-1998 Takashi Kanai
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef _SMD_H
#define _SMD_H

typedef int Id;

/* fundermental items list */

typedef struct _vec {
  double x;
  double y;
  double z;
} Vec;

typedef struct _vec2d {
  double x;
  double y;
} Vec2d;

typedef struct _mat3 {		/* 3-by-3 matrix */
  double   elm[3][3];
} Mat3;

typedef struct _mat4 {		/* 4-by-4 matrix */
  double   elm[4][4];
} Mat4;

//typedef double **Vmtx;

/* matrix structure for linbcg */
typedef struct _semat {
  int    rnum;			/* matrix row */
  int    cnum;			/* matrix column */
  int    num;
  int    *ija;
  double *sa;
  /* constant vectors */
  double *bx, *by, *bz;
  /* solution vectors */
  double *xx, *yy, *zz;
} Semat;

/* "Material" structure */

typedef struct _material {
  float ambient[4];
  float diffuse[4];
  float emission[4];
  float specular[4];
  float shininess[1];
} Material;

/* "Light" structure */

typedef struct _light {
  int       enable;
  float   ambient[4];
  float   diffuse[4];
  float   specular[4];
  float   position[4];
  float   lmodel_ambient[4];
  float   local_view[1];
} Light;

/*************** PPD file format *********************
  node type parameters for memory allocation routines
*******************************************************/

#define PPD_PPD         0
#define PPD_SOLID	1
#define PPD_PART	2
#define PPD_FACE	3
#define PPD_HEDGE       4
#define PPD_NORMAL	5
#define PPD_VERTEX	6
#define PPD_EDGE	7
#define PPD_LOOP	8
#define PPD_POINT	9
#define PPD_UVW		10
#define PPD_TRANS	11
#define PPD_ROT		12
#define PPD_OPT_WEIGHT  13
#define PPD_MATERIAL	14
#define PPD_FNODE	15
#define PPD_NONE	16
#define PPD_HVERTEX     17
#define PPD_HFACE       18
#define PPD_MVERTEX     19
#define PPD_VTED1       20
#define PPD_VTED2       21
#define PPD_HEADER	22

/* loop open or not */
#define OPENLOOP        0
#define CLOSEDLOOP      1
#define SHORTESTPATH    2
#define HLOOP           3

#define MAXVNUM         128
#define TRIANGLE        3

/* type */
#define ORIGINAL        0
#define ADDED           1

/* vertex type */
#define VERTEX_ORIGINAL ORIGINAL
#define VERTEX_ADDED    ADDED

/* edge type */
#define EDGE_ORIGINAL ORIGINAL
#define EDGE_ADDED    ADDED

/* for morphing */
#define SRC             1
#define TARGET          2

/* create from flag */
#define FROM_INTSEC     0
#define FROM_SRC        SRC
#define FROM_TARGET     TARGET
#define FROM_HVERTEX    3

/* ppd structure */
typedef struct _sppd Sppd;
typedef struct _spso Spso;
typedef struct _sppt Sppt;
typedef struct _sphe Sphe;
typedef struct _spfc Spfc;
typedef struct _spnm Spnm;
typedef struct _vtfc Vtfc;
typedef struct _vted Vted;
typedef struct _vtnm Vtnm;
typedef struct _vtvt Vtvt;
typedef struct _spvt Spvt;
typedef struct _sped Sped;
typedef struct _edvt Edvt;
typedef struct _splv Splv;
typedef struct _sple Sple;
typedef struct _splp Splp;

/* for quadtree */
typedef struct _qtree   QTree;
typedef struct _qrange  QRange;
typedef struct _qface   QFace;
typedef struct _qedge   QEdge;
typedef struct _qvertex QVertex;

/* control mesh structure */
typedef struct _hppd    HPpd;
typedef struct _hvertex HVertex;
typedef struct _hedge   HEdge;
typedef struct _hloop   HLoop;
typedef struct _hface   HFace;
typedef struct _hhalfedge HHalfedge;
typedef struct _hedvt   Hedvt;

/* grouping ppd structure */
typedef struct _hgppd   HGppd;
typedef struct _hgfc    HGfc;
typedef struct _hgvt    HGvt;
typedef struct _hgvted  HGvted;
typedef struct _hgvtvt  HGvtvt;
typedef struct _hged    HGed;
typedef struct _hgedvtlist  HGedvtList;
typedef struct _hgedvtnode  HGedvtNode;
typedef struct _hgedvt  HGedvt;
typedef struct _hgeded  HGeded;
typedef struct _hgedlist  HGedList;
typedef struct _hgednode  HGedNode;
typedef struct _hgedarray HGedArray;
typedef struct _hgsf    HGsf;
typedef struct _hghe    HGhe;
typedef struct _hglp    HGlp;
typedef struct _hgcv    HGcv;

/* shortest-path graph structure */
typedef struct _sgraph SGraph;
typedef struct _sgvted SGvted;
typedef struct _sgvt   SGvt;
typedef struct _sged   SGed;
typedef struct _sgfc   SGfc;
typedef struct _sgfcvt SGfcvt;
typedef struct _sglp   SGlp;
typedef struct _sglpvt SGlpvt;
typedef struct _sglped SGlped;
	
/* star structure */
typedef struct _star    Star;
typedef struct _starvt  Starvt;

/* ppd structure */

struct _sppd {
  int sn; int sid; Spso *spso, *epso; /* Solid */
  int pn; int pid; Sppt *sppt, *eppt; /* Part */
  int fn; int fid; Spfc *spfc, *epfc; /* Face */
  int nn; int nid; Spnm *spnm, *epnm; /* Normal */
  int vn; int vid; Spvt *spvt, *epvt; /* Vertex */
  int en; int eid; Sped *sped, *eped; /* Edge */
  int ln; int lid; Splp *splp, *eplp; /* Loop */

  /* Quadtree */
  int qn; QTree *qt;         
  int    maxqtlevel;
  double xmin, xmax, ymin, ymax;

  /* Material */
  Material matl;

  /* Misc */
  double scale;
  Vec    center;

  /* for smooth shading */
  double smooth_angle;

  /* for shortest_path */
  double avr_edge_length;
  double max_edge_length;

  /* morphing vector */
  Vec    *mvec1, *mvec2;
  
  /* morphing vectors are calculated */
  /* もうすぐ必要なくなるはず */
  unsigned short *mcalc1, *mcalc2;
  
  char   filename[BUFSIZ];
};

/* ppd solid structure */
struct _spso {
  Id no;
  Spso *nxt;
  Spso *prv;
};

/* ppd part structure */
struct _sppt {
  Id   no;  
  Spso *bpso;
  Sppt *nxt;
  Sppt *prv;
};

/* ppd face structure */
struct _spfc {
  Id    col;
  Id    no;
  Id    sid;
  Vec   nrm;                   /* normal vector */
  
  int   hen;                     /* number of halfedge */
  Sphe  *sphe;
  Spso  *bpso;                   /* back pointer to ppdsolid */
  Sppt  *bppt;                   /* back pointer to ppdpart */

  /* for copy_ppd */
  Spfc  *nfc;
  
  Spfc  *nxt;
  Spfc  *prv;
};

struct _sphe {
  Id    no;
  Spvt  *vt;
  Spnm  *nm;
  Sped  *ed;
  Spfc  *bpfc;
  Sphe  *nxt;
  Sphe  *prv;
};

/* ppd normal structure */
struct _spnm {
  Id   sid;                    /* vertex Identifier for save */
  Id   no;                    /* vertex exist or not flag */
  Vec  vec;
  Spso *bpso;
  Spnm *nxt;
  Spnm *prv;
};

/* vertex -> edge */
struct _vted {
  
  Sped  *ed;
  Spvt  *vt;
  double angle;
  Vted *nxt;
  Vted *prv;
  
};

/* vertex -> normal */
struct _vtnm {
  int   cnt;
  Spnm  *nm;
  Spvt  *vt;
  Vtnm *nxt;
  Vtnm *prv;
};

#define EMPTY   0
#define EXIST   1
#define DELETED 2

/* constants for creating hppdlod */
/* vertex attributes */
#define VTXINTERNAL     0
#define VTXEXTERNAL     1

/* edge attributes */
#define EDGEBOUNDARY    1
#define EDGEINTERNAL    2

/* constants for shortest-path (new) */
#define VERTEX_SPATH_ORIGINAL 0
#define VERTEX_SPATH_ADDED    1

#define EDGE_SPATH_ORIGINAL   0
#define EDGE_SPATH_ONFACE     1


/* constants for shortest-path, grouping */
#define SP_VERTEX_NORMAL   0
#define SP_VERTEX_STEINER  1
#define SP_VERTEX_BOUNDARY 2
#define SP_VERTEX_HVERTEX  3

#define SP_EDGE_NORMAL   0
#define SP_EDGE_STEINER  1
#define SP_EDGE_BOUNDARY 2

/* PPD priority queue structure */
typedef struct _pqcont {
  double distance;
  Id   id;
  Spvt *tgt_vt;
  Spvt *prv_vt;
} PQCont;
  
typedef struct _pqheap {
  PQCont *pqcont;
  int    size;
  int    last;
} PQHeap;

typedef struct _vtlist {
  Spvt *prv;
  double dis;
} VtList;

/* SGraph priority queue structure */
typedef struct _sgpqcont {
  double distance;
  Id   id;
  SGvt *tgt_vt;
  SGvt *prv_vt;
} SGPQCont;
  
typedef struct _sgpqheap {
  SGPQCont *pqcont;
  int    size;
  int    last;
} SGPQHeap;

typedef struct _sgvtlist {
  SGvt *prv;
  double dis;
} SGVtList;

/* ppd vertex structure */
struct _spvt{
  
  /* original */
  Id    sid;                      /* vertex Identifier for save */
  Id    no;                       /* vertex exist or not flag */
  Id    col;                      /* vertex color */
  Id    type;                     /* vertex type */
  Spso  *bpso;                    /* back pointer to ppdsolid */
  Spvt  *nxt, *prv;
  Vec   vec;                     /* vector */

  /* texture coordinates */
  Vec2d uvw;                     
  
  int   ven; Vted *svted, *evted; /* vertex -> edge link */
  int   vnn; Vtnm *svtnm, *evtnm; /* vertex -> normal link */

  // for SparseMatrix (fairing)
  int	tven;
  int	isConst;

  /* for morphing */ 
  Spvt  *mvt;

  /* for shortest path */
  /*   SGvt *sgvt; */
  
  /* もうすぐいらなくなる? */
  PQCont *pqc;
  int    pq_type;
  
  int    sp_type;
  Sped   *sp_ed;
  double sp_val;
  
  /* number of passing loops */
  int    spn;
  
  /* used only SP_VERTEX_BOUNDARY */
  Splp   *lp;
  
  /* for HGppd */
  HGvt   *hgvt;
  
  /* for grouping */
  int    group_id;

  /* for creating hppdlod */
  int    atr;
  HVertex *hvt;
  
  /* for copy_ppd */
  Spvt   *nvt;

  /* for calc_morphing_vector */
  int    from;
  
};

/* edge -> vertex */
struct _edvt {
  Sped  *ed, *int_ed;
  Spvt  *vt;
  double val;
  Edvt  *nxt, *prv;
};

/* ppd edge structure */
struct _sped {
  
  /* original */
  Id    no;                      /* edge exist or not flag */
  Id    col;                     /* edge color */
  Id    type;                    /* edge type */
  Spvt  *sv, *ev;                /* start end Vertex */
  Spfc  *rf, *lf;
  Sped  *nxt, *prv;

  /* for quadtree */
  /*   QEdge *qe; */
  
  /* edge->vertex */
  int evn; Edvt *sedvt, *eedvt;

  /* for morphing */
  /*   int flag; */
  /*   Sped *med; */

  /* loop check */
  int    used_loop;
  
  /* for shortest-path */
  SGed   *sged;
  
  double length;
  int    num_steiner_point;
  int    sp_type;
  Sped   *org_ed;
  int    cal_subgraph;

  /* for grouping */
  int    group_id;

  /* for creating hppdlod */
  int    atr;

  /* for copy_ppd */
  Sped   *ned;

  /* for checking egde-face links */
  int    fn;

  // for SparseMatrix (fairing)
  double ewt;
};

/* ppd loop structure */

#define LOOPVT_CORNER   0
#define LOOPVT_ONBOUND  1

struct _splv {
  
  Id   no;

  /* not needed(?) */
  Id   type;

  /* links to hgvt ( for hloop ) */
  /* links create in "hloop_to_hgppd" */
  /* links use in "hgfcharmonic" */
  HGvt *hgvt;
  
  /*   Splp *bplp; */
  
  Spvt *vt;
  
  Splv *nxt, *prv;
  
};

struct _sple {
  
  Id   no;
  Sped *ed;
  
  /* links to hgvt ( for hloop ) */
  /* links create in "hloop_to_hgppd" */
  /* links use in "hgfcharmonic" */
  /*   HGed *hged; */
  
  Sple *nxt, *prv;
  
};

struct _splp {
  
  Id   no;
  /* loop type ( open or closed ) */
  Id   type;
  Id   col;
  
  /* number of corner vertices */
  Id   lcvn;

  /* links to loop vertices */
  Id   lvn;
  Splv *splv, *eplv;

  /* links to loop edges */
  Id   len;
  Sple *sple, *eple;

  /* links to _hedge */
  HEdge *hed;
  
  Splp *nxt, *prv;
  
};

/* for quadtree structure */
struct _qrange {
  double xmin;
  double xmax;
  double ymin;
  double ymax;
};

struct _qtree {
  int    level;
  Id     id;
  int    qfn;
  QFace  *sqf, *eqf;
  int    qen;
  QEdge  *sqe, *eqe;
  int    qvn;
  QVertex *sqv, *eqv;
  QRange qr;
  QTree  *child[4];
  QTree  *parent;
};

struct _qedge {
  Sped   *ed;
  QTree  *qt;
  QEdge  *prv;
  QEdge  *nxt;
};

struct _qvertex {
  Spvt   *vt;
  QTree  *qt;
  QVertex  *prv;
  QVertex  *nxt;
};

struct _qface {
  HGsf   *sf;
  QTree  *qt;
  QFace  *prv;
  QFace  *nxt;
};

/* for open ppd structure */
typedef struct _oppd Oppd;
typedef struct _oso  Oso;
typedef struct _opt  Opt;
typedef struct _ovt  Ovt;
typedef struct _onm  Onm;
typedef struct _ofc  Ofc;

struct _oppd {
  Oso *oso;
  Opt *opt;
  Onm *onm;
  Ovt *ovt;
  Ofc *ofc;
};

struct _oso {
  Spso *so;
};

struct _opt {
  Sppt *pt;
};

struct _onm {
  Spnm *nm;
  Spso *so;
};

struct _ovt {
  Spvt *vt;
  Spso *so;
};

struct _ofc {
  Spfc *fc;
  Spso *so;
  Sppt *pt;
};

/* control mesh strucure */
struct _hppd {

  /* components */
  int vn; int vid; HVertex *shvt, *ehvt; /* Vertex */
  int en; int eid; HEdge *shed, *ehed; /* Edge */
  int fn; int fid; HFace *shfc, *ehfc; /* Face */

  /* ppd */
  Sppd *ppd1, *ppd2; /* ppd */
  Sppd *gppd;        /* ppd for morphing output */

  /* for grouping */
  HGppd *hgppd1, *hgppd2;
};

struct _hvertex {
  Id no;
  Id sid;
  Id col;
  Id atr;
  Spvt *vt1, *vt2;
  HVertex *nxt, *prv;
};

struct _hedvt {
  Spvt  *vt;
  double val;
  Hedvt  *nxt, *prv;
};

struct _hedge {
  Id no;
  Id col;
  Id atr;
  
  Splp *lp1, *lp2, *mlp;

  HFace *rf, *lf;

  int evn;
  Hedvt *sedvt, *eedvt;
  
  HVertex *sv, *ev; /* start end Vertex */
  HEdge *nxt, *prv;
};

struct _hface {
  
  Id no;
  Id col;
  Id sid;
  
  /* halfedges */
  int hen; HHalfedge *shhe;

  /* HGppd face */
  HGfc *hgfc1, *hgfc2;

  /* for morphing harmonic group face */
  HGfc *mhgfc;
  
  Vec nrm1, nrm2;
  
  /* closed boundary loop */
  HLoop *hloop;
  
  HFace *nxt, *prv;
};

struct _hloop {

  Splp *lp1, *lp2;

};

struct _hhalfedge {
  
  Id no;
  
  HVertex  *vt;
  HEdge    *hed;
  
  HHalfedge *nxt,*prv;
  
};

/* grouping ppd Structure */

struct _hgppd {
  
  int  nhgfc;
  HGfc *shgfc, *ehgfc;

};
  
struct _hgfc {

  int id;
  
  /* ppd components */
  /* vertices (only whose sp_types are SP_VERTEX_NORMAL */
  int hgvn; HGvt *shgvt, *ehgvt;
  /* edges */
  int hgen; HGed *shged, *ehged;
  
  /* loops (includes ppdvertex whose sp_types are SP_VETEX_BOUNDARY */
  int hgln; HGlp *shglp, *ehglp;
  /* control vertices (only whose sp_types are SP_VERTEX_HVERTEX */
  int hgcn; HGcv *shgcv, *ehgcv;

  /* surfaces */
  int hgsn; HGsf *shgsf, *ehgsf;
  
  /* for calculating barycentric coordinates */
  /*   int  cvn; */
  /*   Spvt **cvt; */
  /*   Spvt *cvt[TRIANGLE]; */
  
  /* hface */
  HFace *hf;

  HGfc  *mhgfc;
  
  /* Quadtree */
  int qn; QTree *qt;         
  int    maxqtlevel;

  HGfc *nxt, *prv;
  
};

/* vertex -> edge */
struct _hgvted {

  HGed *ed;
  double angle;
  
  HGvted *nxt, *prv;
};

/* for linbcg */
/* vertex -> other vertex */
struct _hgvtvt {
  
  Id    id;
  double val;
  
  /*   HGvt *vt; */
  
  HGvtvt *nxt, *prv;

};

struct _hgvt {

  int  no;
  int  sp_type;
  Spvt *vt;

  /* for hgfc_to_ppd */
  Spvt *tmp_vt;
  
  /* for calculating harmonic maps */
  Vec2d  uvw;
  Vec    vec;
  
  Id     sid;
  double vval;
  
  /* links to HGvtvt */
  int  hgvvn; HGvtvt *shgvv, *ehgvv;
  /* links to HGvted */
  int  hgven; HGvted *shgve, *ehgve;

  /* 合成のときに，もう一方の hgfc (hgfc1 なら hgfc2,
     hgfc2 なら hgfc1 )のどのエッジに乗っかっているか */
  int   from;
  HGed  *inc_ed;
  /* 合成のときに，もう一方の hgfc (hgfc1 なら hgfc2,
     hgfc2 なら hgfc1 ) のどの surface に乗っかっているか */
  /* use in "edge_edge_intersection" */
  HGsf  *inc_sf;

  /* used if "hgvt->sp_type != SP_VERTEX_NORMAL" */
  /* used only hgfc1, hgfc2 */
  HGvt *mhgvt;

  /* used for storing HGvted */
  /* used only mhgfc */
  /* used only if "hgvt->sp_type != SP_VERTEX_NORMAL" */
  HGed *startedge;
  HGed *endedge;

  /* for pivoting */
  /* used in "isHGvtLeftSide" */
  int  sign;
  
  HGvt *nxt, *prv;
  
};

struct _hgedvtlist {

  int en;
  HGedvtNode *senode, *eenode;
  
};

struct _hgedvtnode {
  
  HGsf *sf, *ef;
  HGedvt *mate;
  HGed *intsec_ed;
  HGvt *vt;
  int rotation;
  
  HGedvtNode *nxt, *prv;
  
};

#define NUM_INTERSECTION_EDGE      4
#define EDGE_START 0
#define EDGE_END   1

/* use in "edge_edge_intersection" */
/* edge -> vertex */
struct _hgedvt {

  HGvt *vt;
  HGsf *rf, *lf;
  HGedvt *mate;
  HGed *intsec_ed;

  /* use in "HGedCreatemHGed" */
  int rotation;
  HGed *mhged[NUM_INTERSECTION_EDGE];
  
  HGedvt *nxt, *prv;
};

struct _hgedlist {

  int en;
  HGedNode *senode, *eenode;
  
};

struct _hgednode {
  
  HGed *ed;
  HGedNode *nxt, *prv;
  
};

struct _hgedarray {
  
  HGed *ed;
  
};

/* use in "HGedCreatemHGed" */
/* use only hgfc1, hgfc2 */
struct _hgeded {

  HGed *mhged;
  
  HGeded *nxt, *prv;
  
};

struct _hged {

  int  no;
  Sped *ed;
  int  sp_type;

  HGvt *sv, *ev;

  HGsf *rf, *lf;
  /* for calculating harmonic maps */
  Id   sid;

  int hgevn;
  HGedvt *shgev, *ehgev;
  
  /* Boundary Information (sp_type == SP_EDGE_BOUNDARY) */
  /* Backpointer to HEdge */
  HEdge *hed;

  /* use in "edge_edge_intersection" */
  int pass;
  
  /* use in "HGedCreatemHGed" */
  /* use only hgfc1, hgfc2 */
  int mhgedn;
  HGeded *smhged, *emhged;
  
  HGed *nxt, *prv;
  
};

struct _hgsf {

  int  no;
  Vec  nrm;

  /*   Sphe  *sphe; */
  int   hen;
  HGhe  *shghe;
  
  /*   HGvt *vt[TRIANGLE]; */
  /*   HGed *ed[TRIANGLE]; */

  QFace *qf;
  
  HGsf *nxt, *prv;
  
};

struct _hghe {
  Id    no;
  HGvt  *vt;
  HGed  *ed;
  HGsf  *bhgsf;
  HGhe  *nxt;
  HGhe  *prv;
};

struct _hglp {

  Splp *lp;
  HGlp *nxt, *prv;
  
};
  
struct _hgcv {

  Spvt *vt;
  HGcv *nxt, *prv;
  
};

/* shortest-path graph structure */
struct _sgraph {

  int  sgvtn, sgvtid;
  SGvt *sgvt, *egvt;
  
  int  sgedn, sgedid;
  SGed *sged, *eged;

  int  sgfcn, sgfcid;
  SGfc *sgfc, *egfc;

  SGvt *src, *dist;

  SGlp *lp;
};

/* SGvt to SGed link */
struct _sgvted {
  
  SGed *ed;

  SGvted *nxt, *prv;
  
};
  
struct _sgvt {

  int no;
  int sid;
  unsigned short type;

  /* type = VERTEX_SPATH_ORIGINAL */
  Spvt *spvt;
  /* type = VERTEX_SPATH_ADDED */
  Sped *sped;
  
  /* 3D coordinates */
  Vec  vec;
  
  /* links to the neighbor edge */
  int  sgvtedn;
  SGvted *svted, *evted;

  /* next vertex */
  SGvt *nxt, *prv;

  /* for priority queue */
  SGPQCont *pqc;
  int    pq_type;
  
};

struct _sged {

  int no;
  int sid;
  unsigned short type;

  /* type = EDGE_SPATH_ORIGINAL */
  /* an original edge */
  Sped *sped;

  /* type = EDGE_SPATH_ONFACE */
  /* an original face */
  Spfc *spfc;
  
  /* SGed -> SGvt link */
  SGvt *sv, *ev;

  /* SGfc */
  SGfc *lf, *rf;
  
  /* next edge */
  SGed *nxt, *prv;

  double length;
};

struct _sgfcvt {

  SGvt *vt;

  SGfcvt *nxt, *prv;
  
};

struct _sgfc {

  int   no;
  int   sid;
  Spfc *spfc;

  int     sgfcvtn;
  SGfcvt *sfcvt, *efcvt;

  SGfc *nxt, *prv;
};
  
struct _sglp {

  int  sglpvtn;
  SGlpvt *slpvt, *elpvt;
  
  int  sglpedn;
  SGlped *slped, *elped;

  double length;
  
};

struct _sglpvt {

  SGvt *vt;
  SGlpvt *nxt, *prv;
  
};

struct _sglped {

  SGed *ed;
  SGlped *nxt, *prv;

};

/* star structure */

struct _starvt {

  Id   no;
  Spvt *vt;
  Starvt *nxt, *prv;

};

struct _star {

  int vn;
  Starvt *spvt, *epvt;

  Sped *e;
  Spvt *sv, *ev;

};

/***********  window attributes structure *************/

/* "Pers" structure */

typedef struct _pers {
  double scraspct;		/* aspect ratio value */
  double angle;			/* the angle of the field of view */
  double znear_ratio;		/* znear plane ratio value */
  double zfar_ratio;		/* zfar plane ratio value */
  double fd;			/* focal distance */
  Vec    eye_dir;		/* eye direction */
  Vec    ref;			/* reference point vector */
  Vec    up;                     /* up vector */
} Pers;

/* edit constants */
/* number of constants should be linked to the "edit_tb" arrays */
#define EDIT_CREATE_PPDLOOP     0
#define EDIT_DELETE_PPDLOOP		1
#define EDIT_CREATE_PPDFACE     2
#define EDIT_DELETE_PPDFACE		3
#define EDIT_CREATE_CV			4
#define EDIT_MOVE_CV			5
#define EDIT_DELETE_CV			6
#define EDIT_CREATE_CMESH		7
#define EDIT_DELETE_CMESH		8
#define EDIT_CREATE_SPATH		9
#define EDIT_DELETE_SPATH		10
#define EDIT_CREATE_SPATH_MANU	11
#define EDIT_NONE				12

/* select constants */

#define SELECTNONE      0
#define SELECTED        1
#define NONSELECTED     0
#define SELMAX          1000

#define SEL_VERTEX      1
#define SEL_EDGE        2
#define SEL_FACE        3
#define SEL_CLEAR       0

typedef struct _sellist SelList;

struct _sellist {
  
  int     pid;
  
  Spvt    *vt;
  Spfc    *fc;
  Splp    *lp;
  HVertex *hvt;
  HFace   *hfc;
  
  SelList *nxt, *prv;
};

#define SCREEN_SRC         0
#define SCREEN_DIST        1

typedef struct _screenatr {
  int            no;
  int            type;                    /* screen type (2D, 3D) */
  int            resize;
  //  Widget         glw;
  //  XVisualInfo    *vi;
  //  GLXContext     xc;
  //  Widget         fr3d;
  CWnd *wnd;

  /* width, height */
  int            width;
  int            height;
  double         xcenter;
  double         ycenter;

  /* background color */
  float          bgrgb[3];

  /* font */
  unsigned int   fontOffset;

  /* zoom parameter */
  int            zoom_active;
  float          zoom;

  /* rotate parameter */
  int            rotate_active;
  int            rotate_type;
  double         rotate_x, rotate_y, rotate_z;
  double         zrot_rad;
  double         rmat[16];
  Vec            rotate_xvec;
  Vec            rotate_yvec;
  Vec            rotate_zvec;

  /* select structure */
  int            sellist_flag;
  int            n_sellist;
  SelList        *sel_first;
  SelList        *sel_last;
  
  /* delete area parameter */
  int            areaflag;
  Vec2d          areaorg;
  Vec2d          areaatv;

  /* light parameter */
  Light          light;

  /* perspective parameter */
  Pers           pers;

  /* current_ppd */
  Sppd           *current_ppd;
  Sppd           *view_ppd;

  double         mmat[16], pmat[16];
  int            viewport[4];

  // radius of sphere and cylinder
  double rad_sph;
  double rad_cyl;

  /* for shortest path */
  SGraph *sg, *nsg;
  SGlp   *lp;

} ScreenAtr;

/* display structure */

typedef struct _display3d {

  int	vertex;
  int wire;
  int shading;
  int coaxis;
  int loop;
  int group;
  int cpoint;
  int cmesh;
  int spath;
  int hmap;
  int area;
  int enhanced;
  int smooth;
  int interp;

} Disp3D;

#define VIEW_ORGMESH   0
#define VIEW_INTPMESH  1

typedef struct _swin {

  // window wize
  int width;
  int height;

  // edit type
  int            edit_type;
  unsigned short select_type;

  // window dependent parameters 
  ScreenAtr screenatr[2];

  // display structure 
  Disp3D    dis3d;

  // default materials 
  Material  *material;

  // menu mode parameters
  // file flag (decide *.<***>) 
  unsigned short filed;
  // file open flag (0 : open 1 : save) 
  unsigned short opend;

  /* Matrix for ps */
  double mmat[16];
  double pmat[16];
  
  /* build gui or not */
  int   prn;

  /* morph ppd */
  Sppd *morph_ppd;
  int  mdiv;

  /* tile display */
  int  tileno;
  
  /* harmonic ppd */
  HPpd *hppd;

  /* for smooth shading */
  //	int smooth_shading;

  /* for displaying vertices as spheres, edges as tubes */
  //	int ext_display;

  /* for making subgraph */
  double sublength;

  /* save harmonic map to postscript file */
  int savehmtops;
  
  /* save morphing results to SGI image files. */
  int saveimg;

  /* view attributes. */
  //	int view_attribs;
  
} Swin;

/*** defines and macros ***/

/* defines */

#define SMD_ON          1
#define SMD_OFF         0
#define SMDNULL         -1
#define SMDZERO         0

#define PNTBLUE         2
#define PNTGREEN        1
#define PNTRED          0

#define EDGEWHITE       2
#define EDGEBLUE        1
#define EDGERED         0

#define FACEBLUE        2
#define FACEGREEN       1
#define FACERED         0

#define LOOPBLUE        1
#define LOOPRED         0

#define NOTCALCURATED   0
#define CALCURATED      1
#define SUCCEED         1
#define FAIL            0
#define INSIDE          0
#define OUTSIDE         1
#define ONLINE          2
#define INTERSECTION    3

/* file */
#define SMDOPEN         0
#define SMDSAVE         1
#define SMDFILEPPD1     0
#define SMDFILEPPD2     1
#define SMDFILEGMH      2
#define SMDFILEGPPD     3

/* rotate */
#define ROTATE_NONE     0
#define ROTATE_XY       1
#define ROTATE_Z        2

/* file */
#define comment(c) (c == '\n' || c == '!' || c == '%' || c == '#' || c == '*')

/* misc */
#define SMDEPS          1.0e-16
#define SMDZEROEPS      1.0e-05
#define SMDPI		3.14159265358979
#define PITIMES2	6.283185	/* 2 * pi */
#define PIOVER2		1.570796	/* pi / 2 */
#define NE		2.718282	/* the venerable e */
#define SQRT2		1.414214	/* sqrt(2) */
#define SQRT3		1.732051	/* sqrt(3) */
#define GOLDEN		1.618034	/* the golden ratio */
#define DTOR		0.017453	/* convert degrees to radians */
#define RTOD		57.29578	/* convert radians to degrees */

#define MULTI           10000.0

/*#define printf smddebug */

extern void display(char *,...);
extern void displayinfo(char *,...);

/*** objects ***/

extern Swin *swin;

#endif // _SMD_H
