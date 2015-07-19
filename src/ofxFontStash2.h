//
//  ofxFontStash2.h
//  ofxFontStash2
//
//  Created by Oriol Ferrer Mesià on 12/7/15.
//
//

#ifndef __ofxFontStash2__ofxFontStash2__
#define __ofxFontStash2__ofxFontStash2__

#include "ofMain.h"

#include "fontstash.h"
#include "glfontstash.h"

#include "ofxFontStashParser.h"
#include "ofxFontStashStyle.h"

#include "ofxTimeMeasurements.h"

class ofxFontStash2{

public:


	ofxFontStash2();
	void setup(int atlasSizePow2);

	bool addFont(const string& fontID, const string& fontFile); //returns fontID


	//simple draw - no multiline awareness
	float draw(const string& text, const ofxFontStashStyle& style, float x, float y);

	void drawFormatted(const string& text, float x, float y);

	void drawFormattedColumn(const string& text, float x, float y, float width);

	void getVerticalMetrics( const ofxFontStashStyle& style, float* ascender, float* descender, float* lineH);

	FONScontext * getFSContext(){return fs;}

protected:

	enum SplitBlockType{
		WORD,
		SEPARATOR
	};


	string toString(SplitBlockType t){
		if (t == WORD) return "WORD";
		else return "SEPARATOR";
	}


	struct SplitTextBlock{
		SplitBlockType type;
		ofxFontStashParser::StyledText styledText;
		SplitTextBlock(SplitBlockType type, string text, ofxFontStashStyle style){
			this->type = type;
			this->styledText.text = text;
			this->styledText.style = style;
		}
		SplitTextBlock(){}
	};

	struct LineElement{
		SplitTextBlock content;
		ofRectangle area;
		LineElement(SplitTextBlock & b, ofRectangle r){
			this->content = b;
			this->area = r;
		}
	};

	struct StyledLine{
		float lineH;
		float lineW;
		vector<LineElement> elements;
		StyledLine(){
			lineH = lineW = 0;
		}
	};

	int getFsID(const string& userFontID);

	float calcWidth(StyledLine & line);
	float calcLineHeight(StyledLine & line);
	
	void applyStyle(const ofxFontStashStyle& style);

	unsigned int toFScolor(const ofColor& c);
	FONScontext * fs;
	map<string, int> fontIDs; //userFontID to fontStashFontID

	vector<SplitTextBlock> splitWords( vector<ofxFontStashParser::StyledText> & blocks);


};

#endif /* defined(__ofxFontStash2__ofxFontStash2__) */
