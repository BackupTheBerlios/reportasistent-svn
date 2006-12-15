<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="eroot" select="document(string($paramsroot//param[@name='elementary']/@value))"/>
<xsl:variable name="ruleroot" select="document(string($paramsroot//param[@name='rule']/@value))"/>
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
    <xsl:if test="@vderivation">
      <xsl:attribute name="vderivation">
        <xsl:value-of select="@vderivation"/>
      </xsl:attribute>
    </xsl:if>
    
    <xsl:apply-templates/>
    
  </literal>
</xsl:template>


<xsl:template match="ptcmod">
  <xsl:attribute name="id">
    <xsl:value-of select="@id"/>
  </xsl:attribute>
  <xsl:apply-templates/>
</xsl:template>


<xsl:template match="APinv">
  <xsl:variable name="attr" select="parent::node()/@mbattribute"/>
  <xsl:variable name="value" select="parent::node()/@value"/>
  <xsl:variable name="expression" select="$eroot//expression[mbattribute=$attr]"/>
  <xsl:variable name="category" select="$eroot//expression[mbattribute=$attr]/categories/category[value=$value
                                         or value='all']"/>
  <xsl:variable name="numberinv" select="count($expression/APinv)"/>
  <xsl:variable name="randvalueinv" select="$random//random[@number=$numberinv]/@lastvalue"/>
  
  <xsl:copy-of select="$expression/APinv[position()=$randvalueinv]/node()"/>
</xsl:template>


<xsl:template match="NPinv">
  <xsl:variable name="attr" select="parent::node()/@mbattribute"/>
  <xsl:variable name="value" select="parent::node()/@value"/>
  <xsl:variable name="expression" select="$eroot//expression[mbattribute=$attr]"/>
  <xsl:variable name="category" select="$eroot//expression[mbattribute=$attr]/categories/category[value=$value
                                         or value='all']"/>
  <xsl:variable name="numberinv" select="count($expression/NPinv)"/>
  <xsl:variable name="randvalueinv" select="$random//random[@number=$numberinv]/@lastvalue"/>
  
  <xsl:copy-of select="$expression/NPinv[position()=$randvalueinv]/node()"/>
</xsl:template>


<xsl:template match="VPinv">
  <xsl:variable name="attr" select="parent::node()/@mbattribute"/>
  <xsl:variable name="value" select="parent::node()/@value"/>
  <xsl:variable name="expression" select="$eroot//expression[mbattribute=$attr]"/>
  <xsl:variable name="category" select="$eroot//expression[mbattribute=$attr]/categories/category[value=$value
                                         or value='all']"/>
  <xsl:variable name="numberinv" select="count($expression/VPinv)"/>
  <xsl:variable name="randvalueinv" select="$random//random[@number=$numberinv]/@lastvalue"/>
  
  <xsl:copy-of select="$expression/VPinv[position()=$randvalueinv]/node()"/>
</xsl:template>


</xsl:stylesheet>