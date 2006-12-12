<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="eroot" select="document(string($paramsroot//param[@name='elementary']/@value))"/>
<xsl:variable name="ruleroot" select="document(string($paramsroot//param[@name='rule']/@value))"/>
<xsl:param name="random" select="document($_randomness)"/>

<xsl:variable name="langparamroot" select="document(string($paramsroot//param[@name='langparam']/@value))"/>
<xsl:variable name="participle.position" select="$langparamroot//langparam[@name='participle.position']/@value"/>

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


<xsl:template match="*">
  <xsl:copy-of select="."/>
</xsl:template>


<xsl:template match="literal">
  <xsl:variable name="attr" select="@mbattribute"/>
  <xsl:variable name="value" select="@value"/>
  <xsl:variable name="expression" select="$eroot//expression[mbattribute=$attr]"/>
  <xsl:variable name="category" select="$eroot//expression[mbattribute=$attr]/categories/category[value=$value
  	or value='all']"/>
  <!-- ulozime aktualne zpracovavany literal -->
  <xsl:variable name="actualliteral" select="."/>

  <literal>
    <xsl:attribute name="mbattribute">
      <xsl:value-of select="@mbattribute"/>
    </xsl:attribute>
    <xsl:attribute name="value">
      <xsl:value-of select="@value"/>
    </xsl:attribute>
    <xsl:attribute name="role">
      <xsl:value-of select="@role"/>
    </xsl:attribute>
    <xsl:attribute name="typeofphrase">
      <xsl:value-of select="@typeofphrase"/>
    </xsl:attribute>
    <xsl:if test="@number">
      <xsl:attribute name="number">
        <xsl:value-of select="@number"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:if test="@case">
      <xsl:attribute name="case">
        <xsl:value-of select="@case"/>
      </xsl:attribute>
    </xsl:if>
    
    <xsl:choose>
    <!--xsl:when test="@typeofphrase='L' and $category/adjphrase[@relposition='L'] != ''">
      <xsl:variable name="number" select="count($category/adjphrase[@relposition='L'])"/>
      <xsl:variable name="randvalue" select="$random//random[@number=$number]/@lastvalue"/>
      <xsl:copy-of select="$category/adjphrase[@relposition='L'][position()=$randvalue]/node()"/>
    </xsl:when-->
    <xsl:when test="@typeofphrase='L'">
      <xsl:choose>
        <xsl:when test=" $category/adjphrase[@relposition='L'] != ''">
	  <xsl:variable name="number" select="count($category/adjphrase[@relposition='L'])"/>
	  <xsl:variable name="randvalue" select="$random//random[@number=$number]/@lastvalue"/>
	  <xsl:copy-of select="$category/adjphrase[@relposition='L'][position()=$randvalue]/node()"/>
	</xsl:when>
	<!-- nezapomenout pridat ptc -->
	<xsl:when test="$category/verbphrase != '' and $participle.position = 'L'">
	  <xsl:variable name="number" select="count($category/verbphrase)"/>
	  <xsl:variable name="randvalue" select="$random//random[@number=$number]/@lastvalue"/>
	  <!-- poznamename si, ze tvorime pricesti -->
	  <xsl:attribute name="vderivation">
            <xsl:value-of select="'ptc'"/>
	  </xsl:attribute>
	  <xsl:copy-of select="$category/verbphrase[position()=$randvalue]/node()"/>
	  
	</xsl:when>
      </xsl:choose>
    </xsl:when>
    
    <xsl:when test="@typeofphrase='N' and $category/nounphrase != ''">
      <xsl:variable name="number" select="count($category/nounphrase)"/>
      <xsl:variable name="randvalue" select="$random//random[@number=$number]/@lastvalue"/>
      <xsl:copy-of select="$category/nounphrase[position()=$randvalue]/node()"/>
    </xsl:when>
    
    <xsl:when test="@typeofphrase='R'">
      <xsl:choose>
        <xsl:when test="$category/adjphrase[@relposition='R'] != ''">
	  <xsl:variable name="number" select="count($category/adjphrase[@relposition='R'])"/>
	  <xsl:variable name="randvalue" select="$random//random[@number=$number]/@lastvalue"/>
	  <xsl:copy-of select="$category/adjphrase[@relposition='R'][position()=$randvalue]/node()"/>
	</xsl:when>
	<!-- nezapomenout pridat ptc -->
	<xsl:when test="$category/verbphrase != '' and $participle.position = 'R'">
	  <xsl:variable name="number" select="count($category/verbphrase)"/>
	  <xsl:variable name="randvalue" select="$random//random[@number=$number]/@lastvalue"/>
	  <!-- poznamename si, ze tvorime pricesti -->
	  <xsl:attribute name="vderivation">
            <xsl:value-of select="'ptc'"/>
	  </xsl:attribute>
	  <xsl:copy-of select="$category/verbphrase[position()=$randvalue]/node()"/>
	  
	</xsl:when>
      </xsl:choose>
    </xsl:when>
    
    <!-- musime se kouknout, jakou spojku ma predchozi literal - musi mit stejnou
         roli a typ fraze -->
    <xsl:when test="@typeofphrase='NA' and $category/NAF != ''">
      <xsl:variable name="type" select="@role"/>
      <xsl:variable name="phrase" select="@typeofphrase"/>
      <xsl:variable name="previouspos" select="count(preceding-sibling::literal[@role=$type and @typeofphrase=$phrase])"/>
      <xsl:variable name="attrconj" select="$ruleroot//cedent[@type=$type]/literal[position()=$previouspos]/@attribute"/>
      <xsl:variable name="valueconj" select="$ruleroot//cedent[@type=$type]/literal[position()=$previouspos]/coefficient/value"/>
      <xsl:variable name="conj" select="$eroot//expression[mbattribute=$attrconj]/categories/category[value=$valueconj
      	or value='all']/NAF/text()"/>
      
      <xsl:if test="normalize-space($category/NAF/text()) != normalize-space($conj)">
        <xsl:value-of select="$category/NAF/text()"/>
      </xsl:if>
      <xsl:variable name="number" select="count($category/nounphrase)"/>
      <xsl:variable name="randvalue" select="$random//random[@number=$number]/@lastvalue"/>
      
      <xsl:variable name="numberinv" select="count($expression/NPinv)"/>
      <xsl:variable name="randvalueinv" select="$random//random[@number=$numberinv]/@lastvalue"/>
      <xsl:call-template name="replace.nounphrase">
	  <xsl:with-param name="text" select="$category/nounphrase[position()=$randvalue]"/>
	  <xsl:with-param name="case" select="$category/NAF/nounphrase/@case"/>
	  <xsl:with-param name="number" select="$category/NAF/nounphrase/@number"/>
	  <xsl:with-param name="npinv" select="$expression/NPinv[position()=$randvalueinv]"/>
	  <xsl:with-param name="express" select="$expression"/>
	</xsl:call-template>
      <!--xsl:copy-of select="$category/nounphrase[position()=$randvalue]/node()"/-->
    </xsl:when>
    
    <xsl:when test="@typeofphrase='V' and $category/verbphrase != ''">
      <xsl:variable name="number" select="count($category/verbphrase)"/>
      <xsl:variable name="randvalue" select="$random//random[@number=$number]/@lastvalue"/>
      <xsl:copy-of select="$category/verbphrase[position()=$randvalue]/node()"/>
    </xsl:when>
  </xsl:choose>
  
  </literal>
</xsl:template>


<xsl:template name="replace.nounphrase">
  <xsl:param name="text"/>
  <xsl:param name="case"/>
  <xsl:param name="number"/>
  <xsl:param name="npinv"/>
  <xsl:param name="express"/>
  
  <xsl:for-each select="$text/node()">
  
    <xsl:choose>
      <xsl:when test="name(.) = 'NPinv'">
      
        <xsl:variable name="numberinv" select="count($express/NPinv)"/>
	<xsl:variable name="randvalueinv" select="$random//random[@number=$numberinv]/@lastvalue"/>
      
        <xsl:call-template name="replace.nounphrase">
	  <xsl:with-param name="text" select="$npinv"/>
	  <xsl:with-param name="case" select="$case"/>
	  <xsl:with-param name="number" select="$number"/>
	  <xsl:with-param name="npinv" select="$npinv"/>
	</xsl:call-template>
      </xsl:when>
      
      <xsl:when test="name(.) = 'word'">
        <word>
	  <xsl:attribute name="class">
	    <xsl:value-of select="@class"/>
	  </xsl:attribute>
	  <xsl:attribute name="pattern">
	    <xsl:value-of select="@pattern"/>
	  </xsl:attribute>
	  
	  <xsl:if test="@vderivation">
	    <xsl:attribute name="vderivation">
	      <xsl:value-of select="@ptc"/>
	    </xsl:attribute>
	  </xsl:if>
	  
	  <xsl:choose>
	    <xsl:when test="@case">
	      <xsl:attribute name="case">
		<xsl:value-of select="@case"/>
	      </xsl:attribute>
	    </xsl:when>
	    <xsl:otherwise>
	      <xsl:if test="$case">
		<xsl:attribute name="case">
		  <xsl:value-of select="$case"/>
		</xsl:attribute>
	      </xsl:if>
	    </xsl:otherwise>
	  </xsl:choose>
	  
	  <xsl:choose>
	    <xsl:when test="@number">
	      <xsl:attribute name="number">
		<xsl:value-of select="@number"/>
	      </xsl:attribute>
	    </xsl:when>
	    <xsl:otherwise>
	      <xsl:if test="$number">
		<xsl:attribute name="number">
		  <xsl:value-of select="$number"/>
		</xsl:attribute>
	      </xsl:if>
	    </xsl:otherwise>
	  </xsl:choose>
	  
	  <xsl:value-of select="."/>
        </word>
      </xsl:when>
    
      <xsl:otherwise>
	<xsl:copy-of select="."/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:for-each> 
</xsl:template>


</xsl:stylesheet>