<?xml version="1.0" encoding="utf-8"?>

<!-- Styl vybere vhodné formulační vzory podle počtu literálů v antecedentu
     a sukcedentu. Každý formulační vzor je použit tolikrát, kolik je vhodných
     elementů FPA se symbolem Y. -->
     
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="fproot" select="/"/>
<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="fparoot" select="document(string($paramsroot//param[@name='fpa']/@value))"/>
<xsl:variable name="quantifier" select="$paramsroot//param[@name='quantifier']/@value"/>
<xsl:variable name="numofantcon" select="$paramsroot//param[@name='numofantcon']/@value"/>
<xsl:variable name="numofsuccon" select="$paramsroot//param[@name='numofsuccon']/@value"/>
<xsl:variable name="numofconcon" select="$paramsroot//param[@name='numofconcon']/@value"/>


<xsl:template match="/">

<sentences>
  <!-- vybereme vsechny symboly fpa z vyhovujicich formulacnich vzoru -->
  <xsl:for-each select="$fproot//fp[@quantifier=$quantifier
      and contains($numofantcon, concat(@numofant, '#'))
      and contains($numofsuccon, concat(@numofsuc, '#'))
      and contains($numofconcon, concat(@numofcon, '#')) and @show='yes']/fpa[@symbol='Y']">


    <xsl:variable name="fpattern" select="."/>
    
    <!-- v kazdem f. vzoru nahradime element FPA s atributem symbol Y;
         f. vzor kopirujeme tolikkrat, koli je vhodnych FPA -->
    <xsl:for-each select="$fparoot/auxiliarysymbols/fpadata[@symbol='Y'
	and contains($numofantcon, concat(@numofant, '#'))
        and contains($numofsuccon, concat(@numofsuc, '#'))
		and contains($numofconcon, concat(@numofcon, '#'))  and @show='yes']">
      
      <sentence>
	<xsl:copy-of select="$fpattern/preceding-sibling::node()"/>
	
	<fpa>
	  <xsl:attribute name="symbol">
	    <xsl:value-of select="$fpattern/@symbol"/>
	  </xsl:attribute>
	  <xsl:if test="$fpattern/@case">
	    <xsl:attribute name="case">
	      <xsl:value-of select="$fpattern/@case"/>
	    </xsl:attribute>
	  </xsl:if>
	  <xsl:if test="$fpattern/@number">
	    <xsl:attribute name="number">
	      <xsl:value-of select="$fpattern/@number"/>
	    </xsl:attribute>
	  </xsl:if>
	  
	  <xsl:copy-of select="./node()"/>
	</fpa>
	
	<xsl:copy-of select="$fpattern/following-sibling::node()"/>
      </sentence>
	
    </xsl:for-each>
   <!-- /xsl:if -->
  </xsl:for-each>
  
  <!-- musime doplnit vzory, ktere neobsahuji Y, tudiz se nedostaly
       do predchoziho kola -->
  <xsl:for-each select="$fproot//fp[@quantifier=$quantifier
      and contains($numofantcon, concat(@numofant, '#'))
      and contains($numofsuccon, concat(@numofsuc, '#'))
	  and contains($numofconcon, concat(@numofcon, '#'))  and @show='yes']">
    <xsl:if test="boolean(fpa[@symbol='Y']) = false">
      <sentence>
	<xsl:copy-of select="node()"/>
      </sentence>
    </xsl:if>
  </xsl:for-each>
</sentences>

</xsl:template>


</xsl:stylesheet>