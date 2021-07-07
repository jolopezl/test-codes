void MultiGaus(const TVectorD& parMeans, const TMatrixDSym& covMatrix, TVectorD& genPars)
{
    int nPars = parMeans.GetNrows();
    if (nPars <= 0) {
        Error("MultiGaus", "Must have >0 pars");
        return;
    }
    if (covMatrix.GetNrows() != nPars) {
        Error("MultiGaus", "parMeans.GetNrows() != covMatrix.GetNrows()");
        return;
    }

    // Check that covMatrix is symmetric
    for (int iRow = 0; iRow < nPars; iRow++) {
        for (int iCol = iRow; iCol < nPars; iCol++) {
            if (covMatrix(iRow, iCol) != covMatrix(iCol, iRow)) {
                Error("MultiGaus", "malformed cov matrix at row %d, col %d", iRow, iCol);
                return;
            }
        }
    }

    genPars.ResizeTo(nPars);

    TMatrixDSymEigen eigenvariances(covMatrix);
    TVectorD rotParMeans = eigenvariances.GetEigenVectors() * parMeans;
    for (int iPar = 0; iPar < nPars; iPar++) {
        double variance = eigenvariances.GetEigenValues()[iPar];
        // check for positive-definiteness of covMatrix
        if (variance < 0) {
            Error("MultiGaus", "Got a negative eigenvariance (%f) on iPar = %d", variance, iPar);
        }
        genPars[iPar] = gRandom->Gaus(rotParMeans[iPar], sqrt(variance));
    }
    genPars = eigenvariances.GetEigenVectors() * genPars;
}

void test_multigaus()
{
    int nDim = 3;
    TVectorD parMeans(nDim);
    TVectorD parErrors(nDim);
    TMatrixDSym covMatrix(nDim);
    TVectorD genPars(nDim);

    parMeans(0) = 2.91532;
    parMeans(1) = 7.27808;
    parMeans(2) = -0.0278996;
    parErrors(0) = 2.62821e+00;
    parErrors(1) = 2.41538e-01;
    parErrors(2) = 4.81277e-03;
    covMatrix(0, 0) = parErrors(0) * parErrors(0);
    covMatrix(0, 1) = -0.462 * parErrors(0) * parErrors(1);
    covMatrix(0, 2) = 0.772 * parErrors(0) * parErrors(2);

    covMatrix(1, 0) = covMatrix(0, 1);
    covMatrix(1, 1) = parErrors(1) * parErrors(1);
    covMatrix(1, 2) = -0.103 * parErrors(1) * parErrors(2);

    covMatrix(2, 0) = covMatrix(0, 2);
    covMatrix(2, 1) = covMatrix(1, 2);
    covMatrix(2, 2) = parErrors(2) * parErrors(2);

    TFile fout("test.root", "RECREATE");
    TTree t("t", "t tree");
    t.Branch("g0", &genPars(0), "g0/D");
    t.Branch("g1", &genPars(1), "g1/D");
    t.Branch("g2", &genPars(2), "g2/D");

    TH1F* hX = new TH1F("hX", "hX;x;Counts", 100, -10, 15);
    TH1F* hY = new TH1F("hY", "hY;y;Counts", 100, 5, 10);
    TH1F* hZ = new TH1F("hZ", "hZ;z;Counts", 100, -0.1, 0.1);
    TH2F* hXY = new TH2F("hXY", "hXY;x;y;Counts", 100, -10, 15, 100, 5, 10);
    TH2F* hXZ = new TH2F("hXZ", "hXZ;x;z;Counts", 100, -10, 15, 100, -0.1, 0.1);
    TH2F* hYZ = new TH2F("hYZ", "hYZ;y;z;Counts", 100, 5, 10, 100, -0.1, 0.1);

    for (int i = 0; i < 10000; ++i) {
        MultiGaus(parMeans, covMatrix, genPars);
        t.Fill();

        auto x = genPars[0];
        auto y = genPars[1];
        auto z = genPars[2];
        hX->Fill(x);
        hY->Fill(y);
        hZ->Fill(z);
        hXY->Fill(x, y);
        hXZ->Fill(x, z);
        hYZ->Fill(y, z);
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
    c->SaveAs("test_multigaus.png");

    fout.Write();
    fout.Close();
}
