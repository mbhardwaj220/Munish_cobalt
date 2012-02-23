/*
 * Copyright © 2011  Google, Inc.
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Google Author(s): Behdad Esfahbod
 */

#ifndef HB_OT_SHAPE_COMPLEX_ARABIC_TABLE_HH
#define HB_OT_SHAPE_COMPLEX_ARABIC_TABLE_HH

#include "hb-private.hh"


/* == Start of generated table == */
/*
 * The following table is generated by running:
 *
 *   ./gen-arabic-table.py ArabicShaping.txt
 *
 * on files with these headers:
 *
 * # ArabicShaping-6.1.0.txt
 * # Date: 2011-04-15, 23:16:00 GMT [KW]
 */
static const uint8_t joining_table[] =
{

  /* Arabic Characters */

  JOINING_TYPE_U, /* 0600; ARABIC NUMBER SIGN; U; No_Joining_Group */
  JOINING_TYPE_U, /* 0601; ARABIC SIGN SANAH; U; No_Joining_Group */
  JOINING_TYPE_U, /* 0602; ARABIC FOOTNOTE MARKER; U; No_Joining_Group */
  JOINING_TYPE_U, /* 0603; ARABIC SIGN SAFHA; U; No_Joining_Group */
  JOINING_TYPE_U, /* 0604; ARABIC SIGN SAMVAT; U; No_Joining_Group */
  JOINING_TYPE_X, /* 0605 */
  JOINING_TYPE_X, /* 0606 */
  JOINING_TYPE_X, /* 0607 */
  JOINING_TYPE_U, /* 0608; ARABIC RAY; U; No_Joining_Group */
  JOINING_TYPE_X, /* 0609 */
  JOINING_TYPE_X, /* 060A */
  JOINING_TYPE_U, /* 060B; AFGHANI SIGN; U; No_Joining_Group */
  JOINING_TYPE_X, /* 060C */
  JOINING_TYPE_X, /* 060D */
  JOINING_TYPE_X, /* 060E */
  JOINING_TYPE_X, /* 060F */
  JOINING_TYPE_X, /* 0610 */
  JOINING_TYPE_X, /* 0611 */
  JOINING_TYPE_X, /* 0612 */
  JOINING_TYPE_X, /* 0613 */
  JOINING_TYPE_X, /* 0614 */
  JOINING_TYPE_X, /* 0615 */
  JOINING_TYPE_X, /* 0616 */
  JOINING_TYPE_X, /* 0617 */
  JOINING_TYPE_X, /* 0618 */
  JOINING_TYPE_X, /* 0619 */
  JOINING_TYPE_X, /* 061A */
  JOINING_TYPE_X, /* 061B */
  JOINING_TYPE_X, /* 061C */
  JOINING_TYPE_X, /* 061D */
  JOINING_TYPE_X, /* 061E */
  JOINING_TYPE_X, /* 061F */
  JOINING_TYPE_D, /* 0620; DOTLESS YEH WITH SEPARATE RING BELOW; D; YEH */
  JOINING_TYPE_U, /* 0621; HAMZA; U; No_Joining_Group */
  JOINING_TYPE_R, /* 0622; ALEF WITH MADDA ABOVE; R; ALEF */
  JOINING_TYPE_R, /* 0623; ALEF WITH HAMZA ABOVE; R; ALEF */
  JOINING_TYPE_R, /* 0624; WAW WITH HAMZA ABOVE; R; WAW */
  JOINING_TYPE_R, /* 0625; ALEF WITH HAMZA BELOW; R; ALEF */
  JOINING_TYPE_D, /* 0626; DOTLESS YEH WITH HAMZA ABOVE; D; YEH */
  JOINING_TYPE_R, /* 0627; ALEF; R; ALEF */
  JOINING_TYPE_D, /* 0628; BEH; D; BEH */
  JOINING_TYPE_R, /* 0629; TEH MARBUTA; R; TEH MARBUTA */
  JOINING_TYPE_D, /* 062A; DOTLESS BEH WITH 2 DOTS ABOVE; D; BEH */
  JOINING_TYPE_D, /* 062B; DOTLESS BEH WITH 3 DOTS ABOVE; D; BEH */
  JOINING_TYPE_D, /* 062C; HAH WITH DOT BELOW; D; HAH */
  JOINING_TYPE_D, /* 062D; HAH; D; HAH */
  JOINING_TYPE_D, /* 062E; HAH WITH DOT ABOVE; D; HAH */
  JOINING_TYPE_R, /* 062F; DAL; R; DAL */
  JOINING_TYPE_R, /* 0630; DAL WITH DOT ABOVE; R; DAL */
  JOINING_TYPE_R, /* 0631; REH; R; REH */
  JOINING_TYPE_R, /* 0632; REH WITH DOT ABOVE; R; REH */
  JOINING_TYPE_D, /* 0633; SEEN; D; SEEN */
  JOINING_TYPE_D, /* 0634; SEEN WITH 3 DOTS ABOVE; D; SEEN */
  JOINING_TYPE_D, /* 0635; SAD; D; SAD */
  JOINING_TYPE_D, /* 0636; SAD WITH DOT ABOVE; D; SAD */
  JOINING_TYPE_D, /* 0637; TAH; D; TAH */
  JOINING_TYPE_D, /* 0638; TAH WITH DOT ABOVE; D; TAH */
  JOINING_TYPE_D, /* 0639; AIN; D; AIN */
  JOINING_TYPE_D, /* 063A; AIN WITH DOT ABOVE; D; AIN */
  JOINING_TYPE_D, /* 063B; KEHEH WITH 2 DOTS ABOVE; D; GAF */
  JOINING_TYPE_D, /* 063C; KEHEH WITH 3 DOTS BELOW; D; GAF */
  JOINING_TYPE_D, /* 063D; FARSI YEH WITH INVERTED V ABOVE; D; FARSI YEH */
  JOINING_TYPE_D, /* 063E; FARSI YEH WITH 2 DOTS ABOVE; D; FARSI YEH */
  JOINING_TYPE_D, /* 063F; FARSI YEH WITH 3 DOTS ABOVE; D; FARSI YEH */
  JOINING_TYPE_C, /* 0640; TATWEEL; C; No_Joining_Group */
  JOINING_TYPE_D, /* 0641; FEH; D; FEH */
  JOINING_TYPE_D, /* 0642; QAF; D; QAF */
  JOINING_TYPE_D, /* 0643; KAF; D; KAF */
  JOINING_TYPE_D, /* 0644; LAM; D; LAM */
  JOINING_TYPE_D, /* 0645; MEEM; D; MEEM */
  JOINING_TYPE_D, /* 0646; NOON; D; NOON */
  JOINING_TYPE_D, /* 0647; HEH; D; HEH */
  JOINING_TYPE_R, /* 0648; WAW; R; WAW */
  JOINING_TYPE_D, /* 0649; DOTLESS YEH; D; YEH */
  JOINING_TYPE_D, /* 064A; YEH; D; YEH */
  JOINING_TYPE_X, /* 064B */
  JOINING_TYPE_X, /* 064C */
  JOINING_TYPE_X, /* 064D */
  JOINING_TYPE_X, /* 064E */
  JOINING_TYPE_X, /* 064F */
  JOINING_TYPE_X, /* 0650 */
  JOINING_TYPE_X, /* 0651 */
  JOINING_TYPE_X, /* 0652 */
  JOINING_TYPE_X, /* 0653 */
  JOINING_TYPE_X, /* 0654 */
  JOINING_TYPE_X, /* 0655 */
  JOINING_TYPE_X, /* 0656 */
  JOINING_TYPE_X, /* 0657 */
  JOINING_TYPE_X, /* 0658 */
  JOINING_TYPE_X, /* 0659 */
  JOINING_TYPE_X, /* 065A */
  JOINING_TYPE_X, /* 065B */
  JOINING_TYPE_X, /* 065C */
  JOINING_TYPE_X, /* 065D */
  JOINING_TYPE_X, /* 065E */
  JOINING_TYPE_X, /* 065F */
  JOINING_TYPE_X, /* 0660 */
  JOINING_TYPE_X, /* 0661 */
  JOINING_TYPE_X, /* 0662 */
  JOINING_TYPE_X, /* 0663 */
  JOINING_TYPE_X, /* 0664 */
  JOINING_TYPE_X, /* 0665 */
  JOINING_TYPE_X, /* 0666 */
  JOINING_TYPE_X, /* 0667 */
  JOINING_TYPE_X, /* 0668 */
  JOINING_TYPE_X, /* 0669 */
  JOINING_TYPE_X, /* 066A */
  JOINING_TYPE_X, /* 066B */
  JOINING_TYPE_X, /* 066C */
  JOINING_TYPE_X, /* 066D */
  JOINING_TYPE_D, /* 066E; DOTLESS BEH; D; BEH */
  JOINING_TYPE_D, /* 066F; DOTLESS QAF; D; QAF */
  JOINING_TYPE_X, /* 0670 */
  JOINING_TYPE_R, /* 0671; ALEF WITH WASLA ABOVE; R; ALEF */
  JOINING_TYPE_R, /* 0672; ALEF WITH WAVY HAMZA ABOVE; R; ALEF */
  JOINING_TYPE_R, /* 0673; ALEF WITH WAVY HAMZA BELOW; R; ALEF */
  JOINING_TYPE_U, /* 0674; HIGH HAMZA; U; No_Joining_Group */
  JOINING_TYPE_R, /* 0675; HIGH HAMZA ALEF; R; ALEF */
  JOINING_TYPE_R, /* 0676; HIGH HAMZA WAW; R; WAW */
  JOINING_TYPE_R, /* 0677; HIGH HAMZA WAW WITH DAMMA ABOVE; R; WAW */
  JOINING_TYPE_D, /* 0678; HIGH HAMZA DOTLESS YEH; D; YEH */
  JOINING_TYPE_D, /* 0679; DOTLESS BEH WITH TAH ABOVE; D; BEH */
  JOINING_TYPE_D, /* 067A; DOTLESS BEH WITH VERTICAL 2 DOTS ABOVE; D; BEH */
  JOINING_TYPE_D, /* 067B; DOTLESS BEH WITH VERTICAL 2 DOTS BELOW; D; BEH */
  JOINING_TYPE_D, /* 067C; DOTLESS BEH WITH ATTACHED RING BELOW AND 2 DOTS ABOVE; D; BEH */
  JOINING_TYPE_D, /* 067D; DOTLESS BEH WITH INVERTED 3 DOTS ABOVE; D; BEH */
  JOINING_TYPE_D, /* 067E; DOTLESS BEH WITH 3 DOTS BELOW; D; BEH */
  JOINING_TYPE_D, /* 067F; DOTLESS BEH WITH 4 DOTS ABOVE; D; BEH */
  JOINING_TYPE_D, /* 0680; DOTLESS BEH WITH 4 DOTS BELOW; D; BEH */
  JOINING_TYPE_D, /* 0681; HAH WITH HAMZA ABOVE; D; HAH */
  JOINING_TYPE_D, /* 0682; HAH WITH VERTICAL 2 DOTS ABOVE; D; HAH */
  JOINING_TYPE_D, /* 0683; HAH WITH 2 DOTS BELOW; D; HAH */
  JOINING_TYPE_D, /* 0684; HAH WITH VERTICAL 2 DOTS BELOW; D; HAH */
  JOINING_TYPE_D, /* 0685; HAH WITH 3 DOTS ABOVE; D; HAH */
  JOINING_TYPE_D, /* 0686; HAH WITH 3 DOTS BELOW; D; HAH */
  JOINING_TYPE_D, /* 0687; HAH WITH 4 DOTS BELOW; D; HAH */
  JOINING_TYPE_R, /* 0688; DAL WITH TAH ABOVE; R; DAL */
  JOINING_TYPE_R, /* 0689; DAL WITH ATTACHED RING BELOW; R; DAL */
  JOINING_TYPE_R, /* 068A; DAL WITH DOT BELOW; R; DAL */
  JOINING_TYPE_R, /* 068B; DAL WITH DOT BELOW AND TAH ABOVE; R; DAL */
  JOINING_TYPE_R, /* 068C; DAL WITH 2 DOTS ABOVE; R; DAL */
  JOINING_TYPE_R, /* 068D; DAL WITH 2 DOTS BELOW; R; DAL */
  JOINING_TYPE_R, /* 068E; DAL WITH 3 DOTS ABOVE; R; DAL */
  JOINING_TYPE_R, /* 068F; DAL WITH INVERTED 3 DOTS ABOVE; R; DAL */
  JOINING_TYPE_R, /* 0690; DAL WITH 4 DOTS ABOVE; R; DAL */
  JOINING_TYPE_R, /* 0691; REH WITH TAH ABOVE; R; REH */
  JOINING_TYPE_R, /* 0692; REH WITH V ABOVE; R; REH */
  JOINING_TYPE_R, /* 0693; REH WITH ATTACHED RING BELOW; R; REH */
  JOINING_TYPE_R, /* 0694; REH WITH DOT BELOW; R; REH */
  JOINING_TYPE_R, /* 0695; REH WITH V BELOW; R; REH */
  JOINING_TYPE_R, /* 0696; REH WITH DOT BELOW AND DOT WITHIN; R; REH */
  JOINING_TYPE_R, /* 0697; REH WITH 2 DOTS ABOVE; R; REH */
  JOINING_TYPE_R, /* 0698; REH WITH 3 DOTS ABOVE; R; REH */
  JOINING_TYPE_R, /* 0699; REH WITH 4 DOTS ABOVE; R; REH */
  JOINING_TYPE_D, /* 069A; SEEN WITH DOT BELOW AND DOT ABOVE; D; SEEN */
  JOINING_TYPE_D, /* 069B; SEEN WITH 3 DOTS BELOW; D; SEEN */
  JOINING_TYPE_D, /* 069C; SEEN WITH 3 DOTS BELOW AND 3 DOTS ABOVE; D; SEEN */
  JOINING_TYPE_D, /* 069D; SAD WITH 2 DOTS BELOW; D; SAD */
  JOINING_TYPE_D, /* 069E; SAD WITH 3 DOTS ABOVE; D; SAD */
  JOINING_TYPE_D, /* 069F; TAH WITH 3 DOTS ABOVE; D; TAH */
  JOINING_TYPE_D, /* 06A0; AIN WITH 3 DOTS ABOVE; D; AIN */
  JOINING_TYPE_D, /* 06A1; DOTLESS FEH; D; FEH */
  JOINING_TYPE_D, /* 06A2; DOTLESS FEH WITH DOT BELOW; D; FEH */
  JOINING_TYPE_D, /* 06A3; FEH WITH DOT BELOW; D; FEH */
  JOINING_TYPE_D, /* 06A4; DOTLESS FEH WITH 3 DOTS ABOVE; D; FEH */
  JOINING_TYPE_D, /* 06A5; DOTLESS FEH WITH 3 DOTS BELOW; D; FEH */
  JOINING_TYPE_D, /* 06A6; DOTLESS FEH WITH 4 DOTS ABOVE; D; FEH */
  JOINING_TYPE_D, /* 06A7; DOTLESS QAF WITH DOT ABOVE; D; QAF */
  JOINING_TYPE_D, /* 06A8; DOTLESS QAF WITH 3 DOTS ABOVE; D; QAF */
  JOINING_TYPE_D, /* 06A9; KEHEH; D; GAF */
  JOINING_TYPE_D, /* 06AA; SWASH KAF; D; SWASH KAF */
  JOINING_TYPE_D, /* 06AB; KEHEH WITH ATTACHED RING BELOW; D; GAF */
  JOINING_TYPE_D, /* 06AC; KAF WITH DOT ABOVE; D; KAF */
  JOINING_TYPE_D, /* 06AD; KAF WITH 3 DOTS ABOVE; D; KAF */
  JOINING_TYPE_D, /* 06AE; KAF WITH 3 DOTS BELOW; D; KAF */
  JOINING_TYPE_D, /* 06AF; GAF; D; GAF */
  JOINING_TYPE_D, /* 06B0; GAF WITH ATTACHED RING BELOW; D; GAF */
  JOINING_TYPE_D, /* 06B1; GAF WITH 2 DOTS ABOVE; D; GAF */
  JOINING_TYPE_D, /* 06B2; GAF WITH 2 DOTS BELOW; D; GAF */
  JOINING_TYPE_D, /* 06B3; GAF WITH VERTICAL 2 DOTS BELOW; D; GAF */
  JOINING_TYPE_D, /* 06B4; GAF WITH 3 DOTS ABOVE; D; GAF */
  JOINING_TYPE_D, /* 06B5; LAM WITH V ABOVE; D; LAM */
  JOINING_TYPE_D, /* 06B6; LAM WITH DOT ABOVE; D; LAM */
  JOINING_TYPE_D, /* 06B7; LAM WITH 3 DOTS ABOVE; D; LAM */
  JOINING_TYPE_D, /* 06B8; LAM WITH 3 DOTS BELOW; D; LAM */
  JOINING_TYPE_D, /* 06B9; NOON WITH DOT BELOW; D; NOON */
  JOINING_TYPE_D, /* 06BA; DOTLESS NOON; D; NOON */
  JOINING_TYPE_D, /* 06BB; DOTLESS NOON WITH TAH ABOVE; D; NOON */
  JOINING_TYPE_D, /* 06BC; NOON WITH ATTACHED RING BELOW; D; NOON */
  JOINING_TYPE_D, /* 06BD; NYA; D; NYA */
  JOINING_TYPE_D, /* 06BE; KNOTTED HEH; D; KNOTTED HEH */
  JOINING_TYPE_D, /* 06BF; HAH WITH 3 DOTS BELOW AND DOT ABOVE; D; HAH */
  JOINING_TYPE_R, /* 06C0; DOTLESS TEH MARBUTA WITH HAMZA ABOVE; R; TEH MARBUTA */
  JOINING_TYPE_D, /* 06C1; HEH GOAL; D; HEH GOAL */
  JOINING_TYPE_D, /* 06C2; HEH GOAL WITH HAMZA ABOVE; D; HEH GOAL */
  JOINING_TYPE_R, /* 06C3; TEH MARBUTA GOAL; R; TEH MARBUTA GOAL */
  JOINING_TYPE_R, /* 06C4; WAW WITH ATTACHED RING WITHIN; R; WAW */
  JOINING_TYPE_R, /* 06C5; WAW WITH BAR; R; WAW */
  JOINING_TYPE_R, /* 06C6; WAW WITH V ABOVE; R; WAW */
  JOINING_TYPE_R, /* 06C7; WAW WITH DAMMA ABOVE; R; WAW */
  JOINING_TYPE_R, /* 06C8; WAW WITH ALEF ABOVE; R; WAW */
  JOINING_TYPE_R, /* 06C9; WAW WITH INVERTED V ABOVE; R; WAW */
  JOINING_TYPE_R, /* 06CA; WAW WITH 2 DOTS ABOVE; R; WAW */
  JOINING_TYPE_R, /* 06CB; WAW WITH 3 DOTS ABOVE; R; WAW */
  JOINING_TYPE_D, /* 06CC; FARSI YEH; D; FARSI YEH */
  JOINING_TYPE_R, /* 06CD; YEH WITH TAIL; R; YEH WITH TAIL */
  JOINING_TYPE_D, /* 06CE; FARSI YEH WITH V ABOVE; D; FARSI YEH */
  JOINING_TYPE_R, /* 06CF; WAW WITH DOT ABOVE; R; WAW */
  JOINING_TYPE_D, /* 06D0; DOTLESS YEH WITH VERTICAL 2 DOTS BELOW; D; YEH */
  JOINING_TYPE_D, /* 06D1; DOTLESS YEH WITH 3 DOTS BELOW; D; YEH */
  JOINING_TYPE_R, /* 06D2; YEH BARREE; R; YEH BARREE */
  JOINING_TYPE_R, /* 06D3; YEH BARREE WITH HAMZA ABOVE; R; YEH BARREE */
  JOINING_TYPE_X, /* 06D4 */
  JOINING_TYPE_R, /* 06D5; DOTLESS TEH MARBUTA; R; TEH MARBUTA */
  JOINING_TYPE_X, /* 06D6 */
  JOINING_TYPE_X, /* 06D7 */
  JOINING_TYPE_X, /* 06D8 */
  JOINING_TYPE_X, /* 06D9 */
  JOINING_TYPE_X, /* 06DA */
  JOINING_TYPE_X, /* 06DB */
  JOINING_TYPE_X, /* 06DC */
  JOINING_TYPE_U, /* 06DD; ARABIC END OF AYAH; U; No_Joining_Group */
  JOINING_TYPE_X, /* 06DE */
  JOINING_TYPE_X, /* 06DF */
  JOINING_TYPE_X, /* 06E0 */
  JOINING_TYPE_X, /* 06E1 */
  JOINING_TYPE_X, /* 06E2 */
  JOINING_TYPE_X, /* 06E3 */
  JOINING_TYPE_X, /* 06E4 */
  JOINING_TYPE_X, /* 06E5 */
  JOINING_TYPE_X, /* 06E6 */
  JOINING_TYPE_X, /* 06E7 */
  JOINING_TYPE_X, /* 06E8 */
  JOINING_TYPE_X, /* 06E9 */
  JOINING_TYPE_X, /* 06EA */
  JOINING_TYPE_X, /* 06EB */
  JOINING_TYPE_X, /* 06EC */
  JOINING_TYPE_X, /* 06ED */
  JOINING_TYPE_R, /* 06EE; DAL WITH INVERTED V ABOVE; R; DAL */
  JOINING_TYPE_R, /* 06EF; REH WITH INVERTED V ABOVE; R; REH */
  JOINING_TYPE_X, /* 06F0 */
  JOINING_TYPE_X, /* 06F1 */
  JOINING_TYPE_X, /* 06F2 */
  JOINING_TYPE_X, /* 06F3 */
  JOINING_TYPE_X, /* 06F4 */
  JOINING_TYPE_X, /* 06F5 */
  JOINING_TYPE_X, /* 06F6 */
  JOINING_TYPE_X, /* 06F7 */
  JOINING_TYPE_X, /* 06F8 */
  JOINING_TYPE_X, /* 06F9 */
  JOINING_TYPE_D, /* 06FA; SEEN WITH DOT BELOW AND 3 DOTS ABOVE; D; SEEN */
  JOINING_TYPE_D, /* 06FB; SAD WITH DOT BELOW AND DOT ABOVE; D; SAD */
  JOINING_TYPE_D, /* 06FC; AIN WITH DOT BELOW AND DOT ABOVE; D; AIN */
  JOINING_TYPE_X, /* 06FD */
  JOINING_TYPE_X, /* 06FE */
  JOINING_TYPE_D, /* 06FF; KNOTTED HEH WITH INVERTED V ABOVE; D; KNOTTED HEH */

  /* Syriac Characters */

  JOINING_TYPE_X, /* 0700 */
  JOINING_TYPE_X, /* 0701 */
  JOINING_TYPE_X, /* 0702 */
  JOINING_TYPE_X, /* 0703 */
  JOINING_TYPE_X, /* 0704 */
  JOINING_TYPE_X, /* 0705 */
  JOINING_TYPE_X, /* 0706 */
  JOINING_TYPE_X, /* 0707 */
  JOINING_TYPE_X, /* 0708 */
  JOINING_TYPE_X, /* 0709 */
  JOINING_TYPE_X, /* 070A */
  JOINING_TYPE_X, /* 070B */
  JOINING_TYPE_X, /* 070C */
  JOINING_TYPE_X, /* 070D */
  JOINING_TYPE_X, /* 070E */
  JOINING_TYPE_X, /* 070F */
  JOINING_GROUP_ALAPH, /* 0710; ALAPH; R; ALAPH */
  JOINING_TYPE_X, /* 0711 */
  JOINING_TYPE_D, /* 0712; BETH; D; BETH */
  JOINING_TYPE_D, /* 0713; GAMAL; D; GAMAL */
  JOINING_TYPE_D, /* 0714; GAMAL GARSHUNI; D; GAMAL */
  JOINING_GROUP_DALATH_RISH, /* 0715; DALATH; R; DALATH RISH */
  JOINING_GROUP_DALATH_RISH, /* 0716; DOTLESS DALATH RISH; R; DALATH RISH */
  JOINING_TYPE_R, /* 0717; HE; R; HE */
  JOINING_TYPE_R, /* 0718; WAW; R; SYRIAC WAW */
  JOINING_TYPE_R, /* 0719; ZAIN; R; ZAIN */
  JOINING_TYPE_D, /* 071A; HETH; D; HETH */
  JOINING_TYPE_D, /* 071B; TETH; D; TETH */
  JOINING_TYPE_D, /* 071C; TETH GARSHUNI; D; TETH */
  JOINING_TYPE_D, /* 071D; YUDH; D; YUDH */
  JOINING_TYPE_R, /* 071E; YUDH HE; R; YUDH HE */
  JOINING_TYPE_D, /* 071F; KAPH; D; KAPH */
  JOINING_TYPE_D, /* 0720; LAMADH; D; LAMADH */
  JOINING_TYPE_D, /* 0721; MIM; D; MIM */
  JOINING_TYPE_D, /* 0722; NUN; D; NUN */
  JOINING_TYPE_D, /* 0723; SEMKATH; D; SEMKATH */
  JOINING_TYPE_D, /* 0724; FINAL SEMKATH; D; FINAL SEMKATH */
  JOINING_TYPE_D, /* 0725; E; D; E */
  JOINING_TYPE_D, /* 0726; PE; D; PE */
  JOINING_TYPE_D, /* 0727; REVERSED PE; D; REVERSED PE */
  JOINING_TYPE_R, /* 0728; SADHE; R; SADHE */
  JOINING_TYPE_D, /* 0729; QAPH; D; QAPH */
  JOINING_GROUP_DALATH_RISH, /* 072A; RISH; R; DALATH RISH */
  JOINING_TYPE_D, /* 072B; SHIN; D; SHIN */
  JOINING_TYPE_R, /* 072C; TAW; R; TAW */
  JOINING_TYPE_D, /* 072D; PERSIAN BHETH; D; BETH */
  JOINING_TYPE_D, /* 072E; PERSIAN GHAMAL; D; GAMAL */
  JOINING_GROUP_DALATH_RISH, /* 072F; PERSIAN DHALATH; R; DALATH RISH */
  JOINING_TYPE_X, /* 0730 */
  JOINING_TYPE_X, /* 0731 */
  JOINING_TYPE_X, /* 0732 */
  JOINING_TYPE_X, /* 0733 */
  JOINING_TYPE_X, /* 0734 */
  JOINING_TYPE_X, /* 0735 */
  JOINING_TYPE_X, /* 0736 */
  JOINING_TYPE_X, /* 0737 */
  JOINING_TYPE_X, /* 0738 */
  JOINING_TYPE_X, /* 0739 */
  JOINING_TYPE_X, /* 073A */
  JOINING_TYPE_X, /* 073B */
  JOINING_TYPE_X, /* 073C */
  JOINING_TYPE_X, /* 073D */
  JOINING_TYPE_X, /* 073E */
  JOINING_TYPE_X, /* 073F */
  JOINING_TYPE_X, /* 0740 */
  JOINING_TYPE_X, /* 0741 */
  JOINING_TYPE_X, /* 0742 */
  JOINING_TYPE_X, /* 0743 */
  JOINING_TYPE_X, /* 0744 */
  JOINING_TYPE_X, /* 0745 */
  JOINING_TYPE_X, /* 0746 */
  JOINING_TYPE_X, /* 0747 */
  JOINING_TYPE_X, /* 0748 */
  JOINING_TYPE_X, /* 0749 */
  JOINING_TYPE_X, /* 074A */
  JOINING_TYPE_X, /* 074B */
  JOINING_TYPE_X, /* 074C */
  JOINING_TYPE_R, /* 074D; SOGDIAN ZHAIN; R; ZHAIN */
  JOINING_TYPE_D, /* 074E; SOGDIAN KHAPH; D; KHAPH */
  JOINING_TYPE_D, /* 074F; SOGDIAN FE; D; FE */

  /* Arabic Supplement Characters */

  JOINING_TYPE_D, /* 0750; DOTLESS BEH WITH HORIZONTAL 3 DOTS BELOW; D; BEH */
  JOINING_TYPE_D, /* 0751; BEH WITH 3 DOTS ABOVE; D; BEH */
  JOINING_TYPE_D, /* 0752; DOTLESS BEH WITH INVERTED 3 DOTS BELOW; D; BEH */
  JOINING_TYPE_D, /* 0753; DOTLESS BEH WITH INVERTED 3 DOTS BELOW AND 2 DOTS ABOVE; D; BEH */
  JOINING_TYPE_D, /* 0754; DOTLESS BEH WITH 2 DOTS BELOW AND DOT ABOVE; D; BEH */
  JOINING_TYPE_D, /* 0755; DOTLESS BEH WITH INVERTED V BELOW; D; BEH */
  JOINING_TYPE_D, /* 0756; DOTLESS BEH WITH V ABOVE; D; BEH */
  JOINING_TYPE_D, /* 0757; HAH WITH 2 DOTS ABOVE; D; HAH */
  JOINING_TYPE_D, /* 0758; HAH WITH INVERTED 3 DOTS BELOW; D; HAH */
  JOINING_TYPE_R, /* 0759; DAL WITH VERTICAL 2 DOTS BELOW AND TAH ABOVE; R; DAL */
  JOINING_TYPE_R, /* 075A; DAL WITH INVERTED V BELOW; R; DAL */
  JOINING_TYPE_R, /* 075B; REH WITH BAR; R; REH */
  JOINING_TYPE_D, /* 075C; SEEN WITH 4 DOTS ABOVE; D; SEEN */
  JOINING_TYPE_D, /* 075D; AIN WITH 2 DOTS ABOVE; D; AIN */
  JOINING_TYPE_D, /* 075E; AIN WITH INVERTED 3 DOTS ABOVE; D; AIN */
  JOINING_TYPE_D, /* 075F; AIN WITH VERTICAL 2 DOTS ABOVE; D; AIN */
  JOINING_TYPE_D, /* 0760; DOTLESS FEH WITH 2 DOTS BELOW; D; FEH */
  JOINING_TYPE_D, /* 0761; DOTLESS FEH WITH INVERTED 3 DOTS BELOW; D; FEH */
  JOINING_TYPE_D, /* 0762; KEHEH WITH DOT ABOVE; D; GAF */
  JOINING_TYPE_D, /* 0763; KEHEH WITH 3 DOTS ABOVE; D; GAF */
  JOINING_TYPE_D, /* 0764; KEHEH WITH INVERTED 3 DOTS BELOW; D; GAF */
  JOINING_TYPE_D, /* 0765; MEEM WITH DOT ABOVE; D; MEEM */
  JOINING_TYPE_D, /* 0766; MEEM WITH DOT BELOW; D; MEEM */
  JOINING_TYPE_D, /* 0767; NOON WITH 2 DOTS BELOW; D; NOON */
  JOINING_TYPE_D, /* 0768; NOON WITH TAH ABOVE; D; NOON */
  JOINING_TYPE_D, /* 0769; NOON WITH V ABOVE; D; NOON */
  JOINING_TYPE_D, /* 076A; LAM WITH BAR; D; LAM */
  JOINING_TYPE_R, /* 076B; REH WITH VERTICAL 2 DOTS ABOVE; R; REH */
  JOINING_TYPE_R, /* 076C; REH WITH HAMZA ABOVE; R; REH */
  JOINING_TYPE_D, /* 076D; SEEN WITH VERTICAL 2 DOTS ABOVE; D; SEEN */
  JOINING_TYPE_D, /* 076E; HAH WITH TAH BELOW; D; HAH */
  JOINING_TYPE_D, /* 076F; HAH WITH TAH AND 2 DOTS BELOW; D; HAH */
  JOINING_TYPE_D, /* 0770; SEEN WITH 2 DOTS AND TAH ABOVE; D; SEEN */
  JOINING_TYPE_R, /* 0771; REH WITH 2 DOTS AND TAH ABOVE; R; REH */
  JOINING_TYPE_D, /* 0772; HAH WITH TAH ABOVE; D; HAH */
  JOINING_TYPE_R, /* 0773; ALEF WITH DIGIT TWO ABOVE; R; ALEF */
  JOINING_TYPE_R, /* 0774; ALEF WITH DIGIT THREE ABOVE; R; ALEF */
  JOINING_TYPE_D, /* 0775; FARSI YEH WITH DIGIT TWO ABOVE; D; FARSI YEH */
  JOINING_TYPE_D, /* 0776; FARSI YEH WITH DIGIT THREE ABOVE; D; FARSI YEH */
  JOINING_TYPE_D, /* 0777; DOTLESS YEH WITH DIGIT FOUR BELOW; D; YEH */
  JOINING_TYPE_R, /* 0778; WAW WITH DIGIT TWO ABOVE; R; WAW */
  JOINING_TYPE_R, /* 0779; WAW WITH DIGIT THREE ABOVE; R; WAW */
  JOINING_TYPE_D, /* 077A; BURUSHASKI YEH BARREE WITH DIGIT TWO ABOVE; D; BURUSHASKI YEH BARREE */
  JOINING_TYPE_D, /* 077B; BURUSHASKI YEH BARREE WITH DIGIT THREE ABOVE; D; BURUSHASKI YEH BARREE */
  JOINING_TYPE_D, /* 077C; HAH WITH DIGIT FOUR BELOW; D; HAH */
  JOINING_TYPE_D, /* 077D; SEEN WITH DIGIT FOUR ABOVE; D; SEEN */
  JOINING_TYPE_D, /* 077E; SEEN WITH INVERTED V ABOVE; D; SEEN */
  JOINING_TYPE_D, /* 077F; KAF WITH 2 DOTS ABOVE; D; KAF */

  /* N'Ko Characters */

  JOINING_TYPE_X, /* 0780 */
  JOINING_TYPE_X, /* 0781 */
  JOINING_TYPE_X, /* 0782 */
  JOINING_TYPE_X, /* 0783 */
  JOINING_TYPE_X, /* 0784 */
  JOINING_TYPE_X, /* 0785 */
  JOINING_TYPE_X, /* 0786 */
  JOINING_TYPE_X, /* 0787 */
  JOINING_TYPE_X, /* 0788 */
  JOINING_TYPE_X, /* 0789 */
  JOINING_TYPE_X, /* 078A */
  JOINING_TYPE_X, /* 078B */
  JOINING_TYPE_X, /* 078C */
  JOINING_TYPE_X, /* 078D */
  JOINING_TYPE_X, /* 078E */
  JOINING_TYPE_X, /* 078F */
  JOINING_TYPE_X, /* 0790 */
  JOINING_TYPE_X, /* 0791 */
  JOINING_TYPE_X, /* 0792 */
  JOINING_TYPE_X, /* 0793 */
  JOINING_TYPE_X, /* 0794 */
  JOINING_TYPE_X, /* 0795 */
  JOINING_TYPE_X, /* 0796 */
  JOINING_TYPE_X, /* 0797 */
  JOINING_TYPE_X, /* 0798 */
  JOINING_TYPE_X, /* 0799 */
  JOINING_TYPE_X, /* 079A */
  JOINING_TYPE_X, /* 079B */
  JOINING_TYPE_X, /* 079C */
  JOINING_TYPE_X, /* 079D */
  JOINING_TYPE_X, /* 079E */
  JOINING_TYPE_X, /* 079F */
  JOINING_TYPE_X, /* 07A0 */
  JOINING_TYPE_X, /* 07A1 */
  JOINING_TYPE_X, /* 07A2 */
  JOINING_TYPE_X, /* 07A3 */
  JOINING_TYPE_X, /* 07A4 */
  JOINING_TYPE_X, /* 07A5 */
  JOINING_TYPE_X, /* 07A6 */
  JOINING_TYPE_X, /* 07A7 */
  JOINING_TYPE_X, /* 07A8 */
  JOINING_TYPE_X, /* 07A9 */
  JOINING_TYPE_X, /* 07AA */
  JOINING_TYPE_X, /* 07AB */
  JOINING_TYPE_X, /* 07AC */
  JOINING_TYPE_X, /* 07AD */
  JOINING_TYPE_X, /* 07AE */
  JOINING_TYPE_X, /* 07AF */
  JOINING_TYPE_X, /* 07B0 */
  JOINING_TYPE_X, /* 07B1 */
  JOINING_TYPE_X, /* 07B2 */
  JOINING_TYPE_X, /* 07B3 */
  JOINING_TYPE_X, /* 07B4 */
  JOINING_TYPE_X, /* 07B5 */
  JOINING_TYPE_X, /* 07B6 */
  JOINING_TYPE_X, /* 07B7 */
  JOINING_TYPE_X, /* 07B8 */
  JOINING_TYPE_X, /* 07B9 */
  JOINING_TYPE_X, /* 07BA */
  JOINING_TYPE_X, /* 07BB */
  JOINING_TYPE_X, /* 07BC */
  JOINING_TYPE_X, /* 07BD */
  JOINING_TYPE_X, /* 07BE */
  JOINING_TYPE_X, /* 07BF */
  JOINING_TYPE_X, /* 07C0 */
  JOINING_TYPE_X, /* 07C1 */
  JOINING_TYPE_X, /* 07C2 */
  JOINING_TYPE_X, /* 07C3 */
  JOINING_TYPE_X, /* 07C4 */
  JOINING_TYPE_X, /* 07C5 */
  JOINING_TYPE_X, /* 07C6 */
  JOINING_TYPE_X, /* 07C7 */
  JOINING_TYPE_X, /* 07C8 */
  JOINING_TYPE_X, /* 07C9 */
  JOINING_TYPE_D, /* 07CA; NKO A; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07CB; NKO EE; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07CC; NKO I; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07CD; NKO E; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07CE; NKO U; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07CF; NKO OO; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D0; NKO O; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D1; NKO DAGBASINNA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D2; NKO N; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D3; NKO BA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D4; NKO PA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D5; NKO TA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D6; NKO JA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D7; NKO CHA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D8; NKO DA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07D9; NKO RA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07DA; NKO RRA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07DB; NKO SA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07DC; NKO GBA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07DD; NKO FA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07DE; NKO KA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07DF; NKO LA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E0; NKO NA WOLOSO; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E1; NKO MA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E2; NKO NYA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E3; NKO NA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E4; NKO HA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E5; NKO WA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E6; NKO YA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E7; NKO NYA WOLOSO; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E8; NKO JONA JA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07E9; NKO JONA CHA; D; No_Joining_Group */
  JOINING_TYPE_D, /* 07EA; NKO JONA RA; D; No_Joining_Group */
  JOINING_TYPE_X, /* 07EB */
  JOINING_TYPE_X, /* 07EC */
  JOINING_TYPE_X, /* 07ED */
  JOINING_TYPE_X, /* 07EE */
  JOINING_TYPE_X, /* 07EF */
  JOINING_TYPE_X, /* 07F0 */
  JOINING_TYPE_X, /* 07F1 */
  JOINING_TYPE_X, /* 07F2 */
  JOINING_TYPE_X, /* 07F3 */
  JOINING_TYPE_X, /* 07F4 */
  JOINING_TYPE_X, /* 07F5 */
  JOINING_TYPE_X, /* 07F6 */
  JOINING_TYPE_X, /* 07F7 */
  JOINING_TYPE_X, /* 07F8 */
  JOINING_TYPE_X, /* 07F9 */
  JOINING_TYPE_C, /* 07FA; NKO LAJANYALAN; C; No_Joining_Group */

  /* Mandaic Characters */

  JOINING_TYPE_X, /* 07FB */
  JOINING_TYPE_X, /* 07FC */
  JOINING_TYPE_X, /* 07FD */
  JOINING_TYPE_X, /* 07FE */
  JOINING_TYPE_X, /* 07FF */
  JOINING_TYPE_X, /* 0800 */
  JOINING_TYPE_X, /* 0801 */
  JOINING_TYPE_X, /* 0802 */
  JOINING_TYPE_X, /* 0803 */
  JOINING_TYPE_X, /* 0804 */
  JOINING_TYPE_X, /* 0805 */
  JOINING_TYPE_X, /* 0806 */
  JOINING_TYPE_X, /* 0807 */
  JOINING_TYPE_X, /* 0808 */
  JOINING_TYPE_X, /* 0809 */
  JOINING_TYPE_X, /* 080A */
  JOINING_TYPE_X, /* 080B */
  JOINING_TYPE_X, /* 080C */
  JOINING_TYPE_X, /* 080D */
  JOINING_TYPE_X, /* 080E */
  JOINING_TYPE_X, /* 080F */
  JOINING_TYPE_X, /* 0810 */
  JOINING_TYPE_X, /* 0811 */
  JOINING_TYPE_X, /* 0812 */
  JOINING_TYPE_X, /* 0813 */
  JOINING_TYPE_X, /* 0814 */
  JOINING_TYPE_X, /* 0815 */
  JOINING_TYPE_X, /* 0816 */
  JOINING_TYPE_X, /* 0817 */
  JOINING_TYPE_X, /* 0818 */
  JOINING_TYPE_X, /* 0819 */
  JOINING_TYPE_X, /* 081A */
  JOINING_TYPE_X, /* 081B */
  JOINING_TYPE_X, /* 081C */
  JOINING_TYPE_X, /* 081D */
  JOINING_TYPE_X, /* 081E */
  JOINING_TYPE_X, /* 081F */
  JOINING_TYPE_X, /* 0820 */
  JOINING_TYPE_X, /* 0821 */
  JOINING_TYPE_X, /* 0822 */
  JOINING_TYPE_X, /* 0823 */
  JOINING_TYPE_X, /* 0824 */
  JOINING_TYPE_X, /* 0825 */
  JOINING_TYPE_X, /* 0826 */
  JOINING_TYPE_X, /* 0827 */
  JOINING_TYPE_X, /* 0828 */
  JOINING_TYPE_X, /* 0829 */
  JOINING_TYPE_X, /* 082A */
  JOINING_TYPE_X, /* 082B */
  JOINING_TYPE_X, /* 082C */
  JOINING_TYPE_X, /* 082D */
  JOINING_TYPE_X, /* 082E */
  JOINING_TYPE_X, /* 082F */
  JOINING_TYPE_X, /* 0830 */
  JOINING_TYPE_X, /* 0831 */
  JOINING_TYPE_X, /* 0832 */
  JOINING_TYPE_X, /* 0833 */
  JOINING_TYPE_X, /* 0834 */
  JOINING_TYPE_X, /* 0835 */
  JOINING_TYPE_X, /* 0836 */
  JOINING_TYPE_X, /* 0837 */
  JOINING_TYPE_X, /* 0838 */
  JOINING_TYPE_X, /* 0839 */
  JOINING_TYPE_X, /* 083A */
  JOINING_TYPE_X, /* 083B */
  JOINING_TYPE_X, /* 083C */
  JOINING_TYPE_X, /* 083D */
  JOINING_TYPE_X, /* 083E */
  JOINING_TYPE_X, /* 083F */
  JOINING_TYPE_R, /* 0840; MANDAIC HALQA; R; No_Joining_Group */
  JOINING_TYPE_D, /* 0841; MANDAIC AB; D; No_Joining_Group */
  JOINING_TYPE_D, /* 0842; MANDAIC AG; D; No_Joining_Group */
  JOINING_TYPE_D, /* 0843; MANDAIC AD; D; No_Joining_Group */
  JOINING_TYPE_D, /* 0844; MANDAIC AH; D; No_Joining_Group */
  JOINING_TYPE_D, /* 0845; MANDAIC USHENNA; D; No_Joining_Group */
  JOINING_TYPE_R, /* 0846; MANDAIC AZ; R; No_Joining_Group */
  JOINING_TYPE_D, /* 0847; MANDAIC IT; D; No_Joining_Group */
  JOINING_TYPE_D, /* 0848; MANDAIC ATT; D; No_Joining_Group */
  JOINING_TYPE_R, /* 0849; MANDAIC AKSA; R; No_Joining_Group */
  JOINING_TYPE_D, /* 084A; MANDAIC AK; D; No_Joining_Group */
  JOINING_TYPE_D, /* 084B; MANDAIC AL; D; No_Joining_Group */
  JOINING_TYPE_D, /* 084C; MANDAIC AM; D; No_Joining_Group */
  JOINING_TYPE_D, /* 084D; MANDAIC AN; D; No_Joining_Group */
  JOINING_TYPE_D, /* 084E; MANDAIC AS; D; No_Joining_Group */
  JOINING_TYPE_R, /* 084F; MANDAIC IN; R; No_Joining_Group */
  JOINING_TYPE_D, /* 0850; MANDAIC AP; D; No_Joining_Group */
  JOINING_TYPE_D, /* 0851; MANDAIC ASZ; D; No_Joining_Group */
  JOINING_TYPE_D, /* 0852; MANDAIC AQ; D; No_Joining_Group */
  JOINING_TYPE_D, /* 0853; MANDAIC AR; D; No_Joining_Group */
  JOINING_TYPE_R, /* 0854; MANDAIC ASH; R; No_Joining_Group */
  JOINING_TYPE_D, /* 0855; MANDAIC AT; D; No_Joining_Group */
  JOINING_TYPE_U, /* 0856; MANDAIC DUSHENNA; U; No_Joining_Group */
  JOINING_TYPE_U, /* 0857; MANDAIC KAD; U; No_Joining_Group */
  JOINING_TYPE_U, /* 0858; MANDAIC AIN; U; No_Joining_Group */

  /* Arabic Extended-A Characters */

  JOINING_TYPE_X, /* 0859 */
  JOINING_TYPE_X, /* 085A */
  JOINING_TYPE_X, /* 085B */
  JOINING_TYPE_X, /* 085C */
  JOINING_TYPE_X, /* 085D */
  JOINING_TYPE_X, /* 085E */
  JOINING_TYPE_X, /* 085F */
  JOINING_TYPE_X, /* 0860 */
  JOINING_TYPE_X, /* 0861 */
  JOINING_TYPE_X, /* 0862 */
  JOINING_TYPE_X, /* 0863 */
  JOINING_TYPE_X, /* 0864 */
  JOINING_TYPE_X, /* 0865 */
  JOINING_TYPE_X, /* 0866 */
  JOINING_TYPE_X, /* 0867 */
  JOINING_TYPE_X, /* 0868 */
  JOINING_TYPE_X, /* 0869 */
  JOINING_TYPE_X, /* 086A */
  JOINING_TYPE_X, /* 086B */
  JOINING_TYPE_X, /* 086C */
  JOINING_TYPE_X, /* 086D */
  JOINING_TYPE_X, /* 086E */
  JOINING_TYPE_X, /* 086F */
  JOINING_TYPE_X, /* 0870 */
  JOINING_TYPE_X, /* 0871 */
  JOINING_TYPE_X, /* 0872 */
  JOINING_TYPE_X, /* 0873 */
  JOINING_TYPE_X, /* 0874 */
  JOINING_TYPE_X, /* 0875 */
  JOINING_TYPE_X, /* 0876 */
  JOINING_TYPE_X, /* 0877 */
  JOINING_TYPE_X, /* 0878 */
  JOINING_TYPE_X, /* 0879 */
  JOINING_TYPE_X, /* 087A */
  JOINING_TYPE_X, /* 087B */
  JOINING_TYPE_X, /* 087C */
  JOINING_TYPE_X, /* 087D */
  JOINING_TYPE_X, /* 087E */
  JOINING_TYPE_X, /* 087F */
  JOINING_TYPE_X, /* 0880 */
  JOINING_TYPE_X, /* 0881 */
  JOINING_TYPE_X, /* 0882 */
  JOINING_TYPE_X, /* 0883 */
  JOINING_TYPE_X, /* 0884 */
  JOINING_TYPE_X, /* 0885 */
  JOINING_TYPE_X, /* 0886 */
  JOINING_TYPE_X, /* 0887 */
  JOINING_TYPE_X, /* 0888 */
  JOINING_TYPE_X, /* 0889 */
  JOINING_TYPE_X, /* 088A */
  JOINING_TYPE_X, /* 088B */
  JOINING_TYPE_X, /* 088C */
  JOINING_TYPE_X, /* 088D */
  JOINING_TYPE_X, /* 088E */
  JOINING_TYPE_X, /* 088F */
  JOINING_TYPE_X, /* 0890 */
  JOINING_TYPE_X, /* 0891 */
  JOINING_TYPE_X, /* 0892 */
  JOINING_TYPE_X, /* 0893 */
  JOINING_TYPE_X, /* 0894 */
  JOINING_TYPE_X, /* 0895 */
  JOINING_TYPE_X, /* 0896 */
  JOINING_TYPE_X, /* 0897 */
  JOINING_TYPE_X, /* 0898 */
  JOINING_TYPE_X, /* 0899 */
  JOINING_TYPE_X, /* 089A */
  JOINING_TYPE_X, /* 089B */
  JOINING_TYPE_X, /* 089C */
  JOINING_TYPE_X, /* 089D */
  JOINING_TYPE_X, /* 089E */
  JOINING_TYPE_X, /* 089F */
  JOINING_TYPE_D, /* 08A0; DOTLESS BEH WITH V BELOW; D; BEH */
  JOINING_TYPE_X, /* 08A1 */
  JOINING_TYPE_D, /* 08A2; HAH WITH DOT BELOW AND 2 DOTS ABOVE; D; HAH */
  JOINING_TYPE_D, /* 08A3; TAH WITH 2 DOTS ABOVE; D; TAH */
  JOINING_TYPE_D, /* 08A4; DOTLESS FEH WITH DOT BELOW AND 3 DOTS ABOVE; D; FEH */
  JOINING_TYPE_D, /* 08A5; QAF WITH DOT BELOW; D; QAF */
  JOINING_TYPE_D, /* 08A6; LAM WITH DOUBLE BAR; D; LAM */
  JOINING_TYPE_D, /* 08A7; MEEM WITH 3 DOTS ABOVE; D; MEEM */
  JOINING_TYPE_D, /* 08A8; YEH WITH HAMZA ABOVE; D; YEH */
  JOINING_TYPE_D, /* 08A9; YEH WITH DOT ABOVE; D; YEH */
  JOINING_TYPE_R, /* 08AA; REH WITH LOOP; R; REH */
  JOINING_TYPE_R, /* 08AB; WAW WITH DOT WITHIN; R; WAW */
  JOINING_TYPE_R, /* 08AC; ROHINGYA YEH; R; ROHINGYA YEH */

};

#define JOINING_TABLE_FIRST	0x0600
#define JOINING_TABLE_LAST	0x08AC

/* == End of generated table == */


#endif /* HB_OT_SHAPE_COMPLEX_ARABIC_TABLE_HH */
