<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="ruleroot" select="document(string($paramsroot//param[@name='rule']/@value))"/>
<xsl:variable name="paramB" select="$ruleroot//param[@name='B']/@value"/>
<xsl:variable name="paramP" select="$ruleroot//param[@name='P']/@value"/>
<xsl:variable name="paramT" select="$ruleroot//param[@name='T']/@value"/>
<xsl:param name="random" select="document($_randomness)"/>

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
  <!-- Pokud nema literal potomky (je prazdny), vytiskneme <literal>, podle toho
       se pozna neprevedene pravidlo. -->
  <xsl:if test="boolean(node()) = false()">
    <literal></literal>
  </xsl:if>
  
  <xsl:apply-templates/>
</xsl:template>


<xsl:template match="word">
  <word>
    <xsl:attribute name="class">
      <xsl:value-of select="@class"/>
    </xsl:attribute>
    <xsl:attribute name="pattern">
      <xsl:value-of select="@pattern"/>
    </xsl:attribute>
    
    <xsl:if test="@class = 'verb'">
      <xsl:if test="parent::node()[@vderivation = 'ptc']">
	<xsl:attribute name="vderivation">ptc</xsl:attribute>
      </xsl:if>
    </xsl:if>
    
    <xsl:choose>
      <xsl:when test="@case">
        <xsl:attribute name="case">
	  <xsl:value-of select="@case"/>
	</xsl:attribute>
      </xsl:when>
      <xsl:when test="parent::node()/@case">
        <xsl:attribute name="case">
	  <xsl:value-of select="parent::node()/@case"/>
	</xsl:attribute>
      </xsl:when>
    </xsl:choose>
    
    <xsl:choose>
      <xsl:when test="@number">
        <xsl:attribute name="number">
	  <xsl:value-of select="@number"/>
	</xsl:attribute>
      </xsl:when>
      <xsl:when test="parent::node()/@number">
        <xsl:attribute name="number">
	  <xsl:value-of select="parent::node()/@number"/>
	</xsl:attribute>
      </xsl:when>
    </xsl:choose>
    
    <xsl:value-of select="."/>
  </word>
</xsl:template>


<xsl:template match="float">
  <xsl:variable name="literaltype" select="parent::node()/@role"/>
  <xsl:variable name="literalposition" select="count(preceding-sibling::literal[@role=$literaltype]) + 1"/>
  <xsl:variable name="literalnumber" select="count(//literal[@role=$literaltype])"/>
  
  <float>
    <xsl:attribute name="id">
      <xsl:value-of select="@id"/>
    </xsl:attribute>
    <xsl:attribute name="role">
      <xsl:value-of select="parent::node()/@role"/>
    </xsl:attribute>
  
    <xsl:choose>
      <xsl:when test="$literalposition = 1">
	<xsl:attribute name="occno">first</xsl:attribute>
      </xsl:when>
      <xsl:when test="$literalposition = $literalnumber">
	<xsl:attribute name="occno">last</xsl:attribute>
      </xsl:when>
      <xsl:otherwise>
        <xsl:attribute name="occno">
	  <xsl:value-of select="$literalposition"/>
	</xsl:attribute>
      </xsl:otherwise>
    </xsl:choose>
   
    <xsl:value-of select="."/>
  </float>
</xsl:template>


<xsl:template match="optionaltext">
  <xsl:if test="$random//random[@number=2]/@lastvalue = 1">
    <xsl:apply-templates/>
  </xsl:if>
</xsl:template>


<xsl:template match="choosetext">
  <xsl:variable name="number" select="count(variant)"/>
  <xsl:variable name="value" select="$random//random[@number=$number]/@lastvalue"/>
  <xsl:value-of select="variant[position()=$value]"/>
</xsl:template>


<xsl:template match="param">
  <xsl:choose>
  
    <xsl:when test="@name='B'">
      <xsl:value-of select="$paramB"/>
    </xsl:when>
    
    <xsl:when test="@name='P'">
      <xsl:value-of select="format-number($paramP, '#.##')"/>
    </xsl:when>
    
    <xsl:when test="@name='T'">
      <xsl:value-of select="$paramT"/>
    </xsl:when>
    
    <xsl:when test="@name='N'">
      <xsl:variable name="attrvalue" select="parent::node()/@value"/>
      <xsl:choose>
	<xsl:when test="contains($attrvalue, '..')">
	  <xsl:value-of select="concat(substring-before($attrvalue, '..'), '&#8211;', substring-after($attrvalue, '..'))"/>
	</xsl:when>
	<xsl:otherwise>
	  <xsl:value-of select="$attrvalue"/>
	</xsl:otherwise>
      </xsl:choose>
    </xsl:when>
    
  </xsl:choose>
</xsl:template>

</xsl:stylesheet>