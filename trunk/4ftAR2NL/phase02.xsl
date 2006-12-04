<?xml version="1.0" encoding="utf-8"?>

<!-- Styl provede za symboly X a Z. Musí se pouštět 2x, protože FPA pro Z může
     obsahovat symbol X. -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="fparoot" select="document(string($paramsroot//param[@name='fpa']/@value))"/>
<xsl:variable name="random" select="document($_randomness)"/>
<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="numofantcon" select="$paramsroot//param[@name='numofantcon']/@value"/>
<xsl:variable name="numofsuccon" select="$paramsroot//param[@name='numofsuccon']/@value"/>
<xsl:variable name="numofconcon" select="$paramsroot//param[@name='numofconcon']/@value"/>


<xsl:template match="/sentences">
  <sentences>
    <xsl:apply-templates/>
  </sentences>
</xsl:template>

<xsl:template match="sentence">
  <sentence>
    <xsl:apply-templates/>
  </sentence>
</xsl:template>


<xsl:template match="fpa[@symbol='Y']">
  <xsl:apply-templates/>
</xsl:template>


<xsl:template match="fpa[@symbol='X']">
  <xsl:variable name="countX" select="count($fparoot//fpadata[@symbol='X'
      and contains($numofantcon, concat(@numofant, '#'))
      and contains($numofsuccon, concat(@numofsuc, '#'))
	  and contains($numofconcon, concat(@numofcon, '#'))])"/>
  <xsl:variable name="randvalX" select="$random//random[@number=$countX]/@lastvalue"/>
  
  <xsl:copy-of select="$fparoot/auxiliarysymbols/fpadata[@symbol='X'
	and contains($numofantcon, concat(@numofant, '#'))
	and contains($numofsuccon, concat(@numofsuc, '#'))
    and contains($numofconcon, concat(@numofcon, '#'))][position()=$randvalX]/node()"/>
</xsl:template>


<xsl:template match="fpa[@symbol='Z']">
  <xsl:variable name="countZ" select="count($fparoot//fpadata[@symbol='Z'
      and contains($numofantcon, concat(@numofant, '#'))
      and contains($numofsuccon, concat(@numofsuc, '#'))
	  and contains($numofconcon, concat(@numofcon, '#'))])"/>
  <xsl:variable name="randvalZ" select="$random//random[@number=$countZ]/@lastvalue"/>
  
  <xsl:copy-of select="$fparoot/auxiliarysymbols/fpadata[@symbol='Z'
	and contains($numofantcon, concat(@numofant, '#'))
	and contains($numofsuccon, concat(@numofsuc, '#'))
	and contains($numofconcon, concat(@numofcon, '#'))][position()=$randvalZ]/node()"/>
</xsl:template>


<xsl:template match="fpa[@symbol='C']">
  <xsl:variable name="countZ" select="count($fparoot//fpadata[@symbol='C'
      and contains($numofantcon, concat(@numofant, '#'))
      and contains($numofsuccon, concat(@numofsuc, '#'))
	  and contains($numofconcon, concat(@numofcon, '#'))])"/>
  <xsl:variable name="randvalZ" select="$random//random[@number=$countZ]/@lastvalue"/>
  
  <xsl:copy-of select="$fparoot/auxiliarysymbols/fpadata[@symbol='C'
	and contains($numofantcon, concat(@numofant, '#'))
	and contains($numofsuccon, concat(@numofsuc, '#'))
	and contains($numofconcon, concat(@numofcon, '#'))][position()=$randvalZ]/node()"/>
</xsl:template>

<!-- Pokud entita vyzaduje predani cisla (number), tak nesmime predat pad
     (case). -->
<xsl:template match="ename">
  <ename>
    <xsl:attribute name="symbol">
      <xsl:value-of select="@symbol"/>
    </xsl:attribute>
    
    <xsl:choose>
      <xsl:when test="@number = '_' and parent::node()/@number and 
                      @case = '_'   and parent::node()/@case">
	<xsl:attribute name="number">
	  <xsl:value-of select="parent::node()/@number"/>
	</xsl:attribute>
	<xsl:attribute name="case">
	  <xsl:value-of select="parent::node()/@case"/>
	</xsl:attribute>
      </xsl:when>
      
      <xsl:when test="@number = '_' and parent::node()/@number">
	<xsl:attribute name="number">
	  <xsl:value-of select="parent::node()/@number"/>
	</xsl:attribute>
      </xsl:when>
      
      <xsl:otherwise>
      
        <xsl:choose>
	  <xsl:when test="parent::node()/@number">
	    <xsl:attribute name="number">
	      <xsl:value-of select="parent::node()/@number"/>
	    </xsl:attribute>
	  </xsl:when>
	  <xsl:when test="@number and @number != '_'">
	    <xsl:attribute name="number">
	      <xsl:value-of select="@number"/>
	    </xsl:attribute>
	  </xsl:when>
	</xsl:choose>
	
	<xsl:choose>
	  <xsl:when test="@number = '_'"/>
	  <xsl:otherwise>
	    <xsl:choose>
	    <xsl:when test="parent::node()/@case">
	      <xsl:attribute name="case">
	        <xsl:value-of select="parent::node()/@case"/>
	      </xsl:attribute>
	    </xsl:when>
	    <xsl:when test="@case and @case != '_'">
	      <xsl:attribute name="case">
	        <xsl:value-of select="@case"/>
	      </xsl:attribute>
	    </xsl:when>
	    </xsl:choose>
	  
	  </xsl:otherwise>
	</xsl:choose>
	
      </xsl:otherwise>
    </xsl:choose>
    
  </ename>
</xsl:template>


<!-- u literalu se neprepisuji direktivy novou, na vyzadani se predaji -->
<xsl:template match="literal">
  <literal>
    <xsl:attribute name="role">
      <xsl:value-of select="@role"/>
    </xsl:attribute>
    <xsl:attribute name="typeofphrase">
      <xsl:value-of select="@typeofphrase"/>
    </xsl:attribute>
    <xsl:if test="@vderivation">
      <xsl:attribute name="vderivation">
        <xsl:value-of select="@vderivation"/>
      </xsl:attribute>
    </xsl:if>
    
    <xsl:choose>
      <xsl:when test="@number = '_' and parent::node()/@number">
	<xsl:attribute name="number">
	  <xsl:value-of select="parent::node()/@number"/>
	</xsl:attribute>
      </xsl:when>
      <xsl:when test="@number and @number != '_'">
	<xsl:attribute name="number">
	  <xsl:value-of select="@number"/>
	</xsl:attribute>
      </xsl:when>
    </xsl:choose>
  
    <xsl:choose>
      <xsl:when test="@case = '_' and parent::node()/@case">
	<xsl:attribute name="case">
	  <xsl:value-of select="parent::node()/@case"/>
	</xsl:attribute>
      </xsl:when>
      <xsl:when test="@case and @case != '_'">
	<xsl:attribute name="case">
	  <xsl:value-of select="@case"/>
	</xsl:attribute>
      </xsl:when>
    </xsl:choose>
   
  </literal>
</xsl:template>


<xsl:template match="*">
  <xsl:copy-of select="."/>
</xsl:template>


</xsl:stylesheet>