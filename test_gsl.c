/**
 * Multivariate gaussian random number generation using GSL
 * https://www.gnu.org/software/gsl/doc/html/randist.html#c.gsl_ran_multivariate_gaussian
 * Compile with:
 * g++ -lgsl -lgslcblas -lm `root-config --cflags` `root-config --libs` -Wall test_gsl.c 
 * For additional printing
 * g++ -D DEBUG -lgsl -lgslcblas -lm `root-config --cflags` `root-config --libs` -Wall test_gsl.c 
**/

#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>

int main(void)
{
  printf("Start...");
  const gsl_rng_type* T;
  gsl_rng* r;

  /* create a generator chosen by the
     environment variable GSL_RNG_TYPE */

  gsl_rng_env_setup();

  T = gsl_rng_default;
  r = gsl_rng_alloc(T);

  gsl_vector* fitPars = gsl_vector_alloc(3);
  gsl_vector_set(fitPars, 0, 2.91532);
  gsl_vector_set(fitPars, 1, 7.27808);
  gsl_vector_set(fitPars, 2, -0.0278996);

#ifdef DEBUG
  for (int i = 0; i < 3; i++) {
    printf("v_%d = %g\n", i, gsl_vector_get(fitPars, i));
  }
#else
#endif

  gsl_vector* genPars = gsl_vector_alloc(3);
  gsl_vector_set(genPars, 0, 0);
  gsl_vector_set(genPars, 1, 0);
  gsl_vector_set(genPars, 2, 0);

  gsl_matrix* covMatrix = gsl_matrix_alloc(3, 3);
  gsl_matrix_set_zero(covMatrix);
  gsl_matrix_set(covMatrix, 0, 0, 1.000 * 2.62821e+00 * 2.62821e+00);
  gsl_matrix_set(covMatrix, 0, 1, -0.462 * 2.62821e+00 * 2.41538e-01);
  gsl_matrix_set(covMatrix, 0, 2, 0.772 * 2.62821e+00 * 4.81277e-03);
  gsl_matrix_set(covMatrix, 1, 0, -0.462 * 2.62821e+00 * 2.41538e-01);
  gsl_matrix_set(covMatrix, 1, 1, 1.000 * 2.41538e-01 * 2.41538e-01);
  gsl_matrix_set(covMatrix, 1, 2, -0.103 * 2.41538e-01 * 4.81277e-03);
  gsl_matrix_set(covMatrix, 2, 0, 0.772 * 2.62821e+00 * 4.81277e-03);
  gsl_matrix_set(covMatrix, 2, 1, -0.103 * 2.41538e-01 * 4.81277e-03);
  gsl_matrix_set(covMatrix, 2, 2, 1.000 * 4.81277e-03 * 4.81277e-03);

#ifdef DEBUG
  printf("The covariance matrix is:\n");
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      printf("%f ", gsl_matrix_get(covMatrix, i, j));
    }
    printf("\n");
  }
#else
#endif

  gsl_linalg_cholesky_decomp(covMatrix);

#ifdef DEBUG
  printf("The cholesky_decomp matrix is:\n");
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      printf("%f ", gsl_matrix_get(covMatrix, i, j));
    }
    printf("\n");
  }
#else
#endif

  double g0, g1, g2;

  TFile fout("test_gsl.root", "RECREATE");
  TTree t("t", "t tree");
  t.Branch("g0", &g0, "g0/D");
  t.Branch("g1", &g1, "g1/D");
  t.Branch("g2", &g2, "g2/D");

  TH1F* hX = new TH1F("hX", "hX;x;Counts", 100, -10, 15);
  TH1F* hY = new TH1F("hY", "hY;y;Counts", 100, 5, 10);
  TH1F* hZ = new TH1F("hZ", "hZ;z;Counts", 100, -0.1, 0.1);
  TH2F* hXY = new TH2F("hXY", "hXY;x;y;Counts", 100, -10, 15, 100, 5, 10);
  TH2F* hXZ = new TH2F("hXZ", "hXZ;x;z;Counts", 100, -10, 15, 100, -0.1, 0.1);
  TH2F* hYZ = new TH2F("hYZ", "hYZ;y;z;Counts", 100, 5, 10, 100, -0.1, 0.1);

  for (int sample = 0; sample < 10000; ++sample) {
    gsl_ran_multivariate_gaussian(r, fitPars, covMatrix, genPars);
    g0 = gsl_vector_get(genPars, 0);
    g1 = gsl_vector_get(genPars, 1);
    g2 = gsl_vector_get(genPars, 2);
    t.Fill();

    hX->Fill(g0);
    hY->Fill(g1);
    hZ->Fill(g2);
    hXY->Fill(g0, g1);
    hXZ->Fill(g0, g2);
    hYZ->Fill(g1, g2);
  }

  TCanvas* c = new TCanvas("c", "Multivariate gaussian random numbers", 1200, 600);
  c->Divide(3, 2);
  c->cd(1);
  hX->Draw();
  c->cd(2);
  hY->Draw();
  c->cd(3);
  hZ->Draw();
  c->cd(4);
  hXY->Draw("COL");
  c->cd(5);
  hXZ->Draw("COL");
  c->cd(6);
  hYZ->Draw("COL");
  c->SaveAs("test_gsl_multigaus.png");

  t.Write();
  fout.Close();

  gsl_vector_free(fitPars);
  gsl_vector_free(genPars);
  gsl_matrix_free(covMatrix);
  gsl_rng_free(r);
  return 0;
}
