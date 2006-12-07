<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">


  <!-- nastaveni jazyka (defaultne cestina)-->
  <xsl:variable name="lng">cz</xsl:variable>
  
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="ValuesType">abs</xsl:variable>
<xsl:variable name="GraphTitle">4ft Graph</xsl:variable>
<xsl:variable name="LegendShow">false</xsl:variable>
<xsl:variable name="GraphWidth">75e-2</xsl:variable>
<xsl:variable name="GraphHeight">75e-2</xsl:variable>
<xsl:variable name="Chart1Color">#aa20aa</xsl:variable>
<xsl:variable name="Chart2Color">#4040fc</xsl:variable>
<xsl:variable name="AntecedentLabel">antecedent</xsl:variable>
<xsl:variable name="SuccedentLabel">succedent</xsl:variable>
<xsl:variable name="NotAntecedentLabel">¬ antecedent</xsl:variable>
<xsl:variable name="NotSuccedentLabel">¬ succedent</xsl:variable>



	
<msxsl:script language="JScript" implements-prefix="dedek">

	function max4(a, b, c, d)
	{
		return Math.max(a,b,c,d);
	}
	
	function max2(x, y)
	{
		return Math.max(x,y);
	}
	
	function normalize_value(co, cim)
	{
		return Math.round(100*(co/cim));
	}


</msxsl:script>



  <!--specialni promenna - SpecialString ... pokud je hodnota AntecedentLabel ... NotSuccedentLabel nastavena na tuto
  hodnotu, nahradi se prislusnou hodnotou skutecneho cedentu-->
  <xsl:variable name="SpecialString">***</xsl:variable>
  

	<xsl:template match="hyp_4ft"> <!-- nezpomen prepsat na match="/hyp_4ft" - odebrat lomitko -->


	<!-- hodnoty cisel, souctu a maxima-->
	
	
	<xsl:variable name="sum" select="@a + @b + @c + @d"/>
	<xsl:variable name="sum_r1" select="@a + @b" />
	<xsl:variable name="sum_r2" select="@c + @d" />
	<xsl:variable name="sum_c1" select="@a + @c" />
	<xsl:variable name="sum_c2" select="@b + @d" />
	
	<xsl:variable name="max" select="dedek:max4(number(@a), number(@b), number(@c), number(@d))"/>
	<xsl:variable name="max_r1" select="dedek:max2(number(@a), number(@b))"/>
	<xsl:variable name="max_r2" select="dedek:max2(number(@c), number(@d))"/>
	<xsl:variable name="max_c1" select="dedek:max2(number(@a), number(@c))"/>
	<xsl:variable name="max_c2" select="dedek:max2(number(@b), number(@d))"/>
	
	<!--spocitani hodnot grafu-->
	
	<xsl:variable name="a">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@a), number($max))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_c1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_r1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@a" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="b">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@b), number($max))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_c2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_r1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@b" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="c">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@c), number($max))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_c1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_r2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@c" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="d">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@d), number($max))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_c2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_r2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@d" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

    <!--hodnoty cedentu-->
    <xsl:variable name="antecedent_str">
      <xsl:for-each select="id(@antecedent)/ti_literal">
        <xsl:if test="position()!=1">
          <xsl:text disable-output-escaping="no"> &amp; </xsl:text>
        </xsl:if>
        <xsl:value-of select="@quant"/>
        <xsl:text disable-output-escaping="yes">(</xsl:text>
        <xsl:value-of select="@value"/>
        <xsl:text disable-output-escaping="yes">)</xsl:text>
      </xsl:for-each>
      <xsl:if test="count(id(@antecedent)/ti_literal)=0">
        <xsl:choose>
          <xsl:when test="$lng='cz'">bez omezení</xsl:when>
          <xsl:otherwise>no restriction</xsl:otherwise>
        </xsl:choose>
      </xsl:if>
    </xsl:variable>

    <xsl:variable name="succedent_str">
      <xsl:for-each select="id(@succedent)/ti_literal">
        <xsl:if test="position()!=1">
          <xsl:text disable-output-escaping="no"> &amp; </xsl:text>
        </xsl:if>
        <xsl:value-of select="@quant"/>
        <xsl:text disable-output-escaping="yes">(</xsl:text>
        <xsl:value-of select="@value"/>
        <xsl:text disable-output-escaping="yes">)</xsl:text>
      </xsl:for-each>
      <xsl:if test="count(id(@succedent)/ti_literal)=0">
        <xsl:choose>
          <xsl:when test="$lng='cz'">bez omezení</xsl:when>
          <xsl:otherwise>no restriction</xsl:otherwise>
        </xsl:choose>
      </xsl:if>
    </xsl:variable>

    <!--skutecne labely - popisky grafu-->
    <xsl:variable name="a_label">
      <xsl:choose>
        <xsl:when test="$AntecedentLabel=$SpecialString">
          <xsl:value-of select="$antecedent_str" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$AntecedentLabel"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="na_label">
      <xsl:choose>
        <xsl:when test="$NotAntecedentLabel=$SpecialString">
          <xsl:text>NOT </xsl:text>
          <xsl:value-of select="$antecedent_str" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$NotAntecedentLabel"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="s_label">
      <xsl:choose>
        <xsl:when test="$SuccedentLabel=$SpecialString">
          <xsl:value-of select="$succedent_str" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$SuccedentLabel"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="ns_label">
      <xsl:choose>
        <xsl:when test="$NotSuccedentLabel=$SpecialString">
          <xsl:text>NOT </xsl:text>
          <xsl:value-of select="$succedent_str" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$NotSuccedentLabel"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>



    <paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_4ftgraph">
				<categories id="categories1">
					<category title="{$s_label}" id="category1"></category>
					<category title="{$ns_label}" id="category2"></category>
				</categories>			
				<chart title="{$na_label}" id="chart1" color="{$Chart1Color}">
					<value value="{$c}" id="value3"></value>
					<value value="{$d}" id="value4"></value>
				</chart>
				<chart title="{$a_label}" id="chart2" color="{$Chart2Color}">
					<value value="{$a}" id="value1"></value>
					<value value="{$b}" id="value2"></value>
				</chart>			
			</graph>
		</paragraph>						
	
	</xsl:template>
      




</xsl:stylesheet>
