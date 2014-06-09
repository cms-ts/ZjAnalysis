TLatex* CMSPrel(Float_t Lumi,TString _decaychannel){
  Lumi=4.890;  
  TLatex *latexLabel = new TLatex();
  latexLabel->SetTextSize(0.0275);
  latexLabel->SetTextFont(42);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(0.25,0.35,"CMS Preliminary");
  latexLabel->DrawLatex(0.25,0.30,"#sqrt{s} = 7 TeV  #int Ldt = 4.9 fb^{-1}"); 
  latexLabel->DrawLatex(0.25,0.25,"anti-k_{T} (R = 0.5) PF Jets > 30 GeV");
  latexLabel->DrawLatex(0.25,0.08,_decaychannel);


  return latexLabel;
}

TLatex* CMSPrel(Float_t Lumi,TString _decaychannel,double x, double y){

  TLatex *latexLabel = new TLatex();
  latexLabel->SetTextSize(0.0535);
  latexLabel->SetTextFont(42);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(x,y,"anti-k_{T} (R = 0.5) Jets");
  latexLabel->DrawLatex(x,y-0.06,"p_{T}^{jet} > 30 GeV, |#eta^{jet}| < 2.4");
  latexLabel->DrawLatex(x,y-0.12,_decaychannel);

  TLatex *latexLabel2 = new TLatex();
  latexLabel2->SetTextSize(0.0455);
  latexLabel2->SetTextFont(42);
  latexLabel2->SetLineWidth(2);
  latexLabel2->SetNDC();

  latexLabel2->DrawLatex(0.16,0.965,"CMS Preliminary");
  latexLabel2->DrawLatex(0.16,0.92,"#sqrt{s} = 7 TeV L_{int} = 4.9 fb^{-1}");

  return latexLabel;
}

TLatex* CMSFinal(Float_t Lumi,TString _decaychannel){
  Lumi=4.890;  
  TLatex *latexLabel = new TLatex();
  latexLabel->SetTextSize(0.0275);
  latexLabel->SetTextFont(42);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(0.25,0.35,"CMS");
  latexLabel->DrawLatex(0.25,0.30,"#sqrt{s} = 7 TeV  #int Ldt = 4.9 fb^{-1}"); 
  latexLabel->DrawLatex(0.25,0.25,"anti-k_{T} (R = 0.5) PF Jets > 30 GeV");
  latexLabel->DrawLatex(0.25,0.08,_decaychannel);


  return latexLabel;
}

TLatex* CMSFinal(Float_t Lumi,TString _decaychannel,double x, double y){

  TLatex *latexLabel = new TLatex();
  latexLabel->SetTextFont(43); 
  latexLabel->SetTextSize(22);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(x,y,_decaychannel);
  latexLabel->DrawLatex(x,y-0.07,"anti-k_{T} (R = 0.5) jets");
  latexLabel->DrawLatex(x,y-0.14,"p_{T}^{jet} > 30 GeV, |#eta^{jet}| < 2.4");

  TLatex *latexLabel2 = new TLatex();
  latexLabel2->SetTextFont(43);
  latexLabel2->SetLineWidth(3);
  latexLabel2->SetNDC();

  //  latexLabel2->SetTextSize(30);
  latexLabel2->SetTextSize(26);
  //  latexLabel2->DrawLatex(0.16,0.92,"CMS");
  latexLabel2->DrawLatex(0.16,0.92,"CMS #sqrt{s} = 7 TeV , L = 4.9 fb^{-1}");

  //  latexLabel2->SetTextSize(22);
  //  latexLabel2->DrawLatex(0.52,0.65,"#sqrt{s} = 7 TeV , 4.9 fb^{-1}");

  return latexLabel;
}

TLatex* CMSFinal1(Float_t Lumi,TString _decaychannel,double x, double y){

  TLatex *latexLabel = new TLatex();
  latexLabel->SetTextFont(43); 
  latexLabel->SetTextSize(32);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(x,y,"anti-k_{T} (R = 0.5) jets");
  latexLabel->DrawLatex(x,y-0.07,"p_{T}^{jet} > 30 GeV, |#eta^{jet}| < 2.4");
  latexLabel->DrawLatex(x,y-0.14,_decaychannel);

  TLatex *latexLabel2 = new TLatex();
  latexLabel2->SetTextFont(43);
  latexLabel2->SetTextSize(35);
  latexLabel2->SetLineWidth(3);
  latexLabel2->SetNDC();

  latexLabel2->DrawLatex(0.16,0.92,"CMS #sqrt{s} = 7 TeV L = 4.9 fb^{-1}");

  return latexLabel;
}

Double_t mmTsize(Double_t textsize) {

  Double_t charheight = 0.;
  Double_t pad_width  = gPad->XtoPixel(gPad->GetX2());
  Double_t pad_height = gPad->YtoPixel(gPad->GetY1());
  if (pad_width < pad_height)  charheight = textsize*pad_width;
  else                         charheight = textsize*pad_height;

  // 1 px = 1/96 inch
  // 1 inch = 25.4 mm

  std::cout << "Text size (PAD) = " << textsize << " Character size in mm = " << charheight/96.*25.4 << std::endl;

}
