#ifndef __Mt_Inpand16_H__
#define __Mt_Inpand16_H__

#include "../morphologic16.h"

namespace Filtering { namespace MaskTools { namespace Filters { namespace Morphologic16 { namespace Inpand16 {


extern Processor *inpand_square_stacked_c;
extern Processor *inpand_horizontal_stacked_c;
extern Processor *inpand_vertical_stacked_c;
extern Processor *inpand_both_stacked_c;
extern Processor *inpand_custom_stacked_c;

class Inpand16 : public Morphologic16::MorphologicFilter16
{
public:
    Inpand16(const Parameters& parameters) : Morphologic16::MorphologicFilter16( parameters )
    {
        if (parameters["stacked"].toBool()) {
            /* add the processors */
            if ( parameters["mode"].toString() == "square" )
            {
                processors.push_back(Filtering::Processor<Processor>(inpand_square_stacked_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
            }
            else if ( parameters["mode"].toString() == "horizontal" )
            {
                processors.push_back(Filtering::Processor<Processor>(inpand_horizontal_stacked_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
            }
            else if ( parameters["mode"].toString() == "vertical" )
            {
                processors.push_back(Filtering::Processor<Processor>(inpand_vertical_stacked_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
            }
            else if ( parameters["mode"].toString() == "both" )
            {
                processors.push_back(Filtering::Processor<Processor>(inpand_both_stacked_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
            }
            else
            {
                processors.push_back(Filtering::Processor<Processor>(inpand_custom_stacked_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
                FillCoordinates( parameters["mode"].toString() );
            }
        } else {
            error = "mt_inpand16 doesn't support interleaved input yet";
        }
    }

    static Signature Inpand16::filter_signature()
    {
        Signature signature = "mt_inpand16";

        signature.add( Parameter( TYPE_CLIP, "" ) );
        signature.add( Parameter( 65535, "thY" ) );
        signature.add( Parameter( 65535, "thC" ) );
        signature.add( Parameter( String( "square" ), "mode" ) );
        signature.add( Parameter( false, "stacked" ) );

        return add_defaults( signature );
    }
};

} } } } } // namespace Inpand, Morphologic, Filter, MaskTools, Filtering

#endif