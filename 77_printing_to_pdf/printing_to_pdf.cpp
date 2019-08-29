#include <iostream>
#include <vector>
#include "hpdf.h"


void
error_handler (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void*)
{
    /* throw exception when an error has occured */
    printf ("ERROR: error_no=%04X, detail_no=%d\n", (unsigned int)error_no,     
        (int)detail_no);
    throw std::exception ();
}

struct Movie {
    std::string title;
    std::string year;
    std::string time;
    Movie(const std::string& title_, const std::string& year_, const std::string& time_): 
        title(title_), year(year_), time(time_){};
};

int main(){

    std::vector<Movie> movies = {
        Movie("The Matrix", "1999", "2:16"),
        Movie("Forrest Gump", "1994", "2:22"),
        Movie("The Truman Show", "1998", "1:43"),
        Movie("The Pursuit of Happyness", "2006", "1:57"),
        Movie("Fight Club", "1999", "2:19")
    };

    /* set error-handler when creating a PDF_Doc object  */
    HPDF_Doc pdf = HPDF_New (error_handler, nullptr);
    if (!pdf) {
        std::cout << "error: cannot create PdfDoc object\n";
        return 1;
    }

    try
    {
        HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);
        auto font = HPDF_GetFont (pdf, "Helvetica", NULL);
        auto page = HPDF_AddPage (pdf);
        const auto page_title = "List of movies";

        /* print the title of the page (with positioning center). */
        HPDF_Page_SetFontAndSize (page, font, 24);
        auto tw = HPDF_Page_TextWidth (page, page_title);
        HPDF_Page_BeginText (page);
        HPDF_Page_MoveTextPos (page, (HPDF_Page_GetWidth(page) - tw) / 2,
                    HPDF_Page_GetHeight (page) - 50);
        HPDF_Page_ShowText (page, page_title);
        HPDF_Page_EndText (page);
        HPDF_Page_SetFontAndSize (page, font, 10);
        int counter = 0;
        for(const auto& movie : movies){
            HPDF_Page_BeginText (page);
            HPDF_Page_MoveTextPos (page, 40, HPDF_Page_GetHeight (page) - 100 - counter*15);
            HPDF_Page_ShowText (page, movie.title.c_str());
            HPDF_Page_EndText (page);
            counter++;
        }
        HPDF_SaveToFile (pdf, "test.pdf");
    
    } catch (...) {
        HPDF_Free (pdf);
        return 1;
    }

    /* clean up */
    HPDF_Free (pdf);

    return 0;
    
}