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


<xsl:template match="ptcmodslot">
  <xsl:choose>
    <xsl:when test="parent::node()[@vderivation='ptc']">
      <xsl:variable name="id" select="@id"/>
      <xsl:copy-of select="preceding-sibling::ptcmod[@id=$id]/node()"/>
      <xsl:copy-of select="following-sibling::ptcmod[@id=$id]/node()"/>
    </xsl:when>
    <xsl:otherwise/>
  </xsl:choose>
</xsl:template>


<xsl:template match="ptcmod">
  <xsl:choose>
    <xsl:when test="parent::node()[@vderivation='ptc']"/>
    <!-- obsah ostatnich musime kopirovat, v dalsi fazy pripadne elementy
         "ptcmod" mazeme -->
    <xsl:otherwise>
      <xsl:apply-templates/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


</xsl:stylesheet>