<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="ValuesType">abs</xsl:variable>
<xsl:variable name="DifType">dif_abs</xsl:variable>
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
	
	function difference(x, y, delitel1, delitel2)
	{
	    var d1 = delitel1;
		if (d1 == 0)
			d1 = 1;
		var d2 = delitel2;
		if (d2 == 0)
			d2 = 1;
		return (Math.abs((x/d1) - (y/d2)));
	}
	
	function hodnota(val, nf)
	{
		var delitel = nf;
		if (delitel == 0)
			delitel = 1;
		return (Math.round(100 * (val / delitel)));
	}


</msxsl:script>
	
	
	
	

	<xsl:template match="hyp_sd4ft"> 


	<!-- hodnoty cisel, souctu a maxima-->
	
	
	<xsl:variable name="sum_set1" select="@a + @b + @c + @d"/>
	<xsl:variable name="sum_r1_set1" select="@a + @b" />
	<xsl:variable name="sum_r2_set1" select="@c + @d" />
	<xsl:variable name="sum_c1_set1" select="@a + @c" />
	<xsl:variable name="sum_c2_set1" select="@b + @d" />
	
	<xsl:variable name="max_set1" select="dedek:max4(number(@a), number(@b), number(@c), number(@d))"/>
	<xsl:variable name="max_r1_set1" select="dedek:max2(number(@a), number(@b))"/>
	<xsl:variable name="max_r2_set1" select="dedek:max2(number(@c), number(@d))"/>
	<xsl:variable name="max_c1_set1" select="dedek:max2(number(@a), number(@c))"/>
	<xsl:variable name="max_c2_set1" select="dedek:max2(number(@b), number(@d))"/>
	
	<xsl:variable name="sum_set2" select="@e + @f + @g + @h"/>
	<xsl:variable name="sum_r1_set2" select="@e + @f" />
	<xsl:variable name="sum_r2_set2" select="@g + @h" />
	<xsl:variable name="sum_c1_set2" select="@e + @g" />
	<xsl:variable name="sum_c2_set2" select="@f + @h" />
	
	<xsl:variable name="max_set2" select="dedek:max4(number(@e), number(@f), number(@g), number(@h))"/>
	<xsl:variable name="max_r1_set2" select="dedek:max2(number(@e), number(@f))"/>
	<xsl:variable name="max_r2_set2" select="dedek:max2(number(@g), number(@h))"/>
	<xsl:variable name="max_c1_set2" select="dedek:max2(number(@e), number(@g))"/>
	<xsl:variable name="max_c2_set2" select="dedek:max2(number(@f), number(@h))"/>
	
	<!--spocitani hodnot grafu-->
	
	<xsl:variable name="delitel1">
		<xsl:choose>
			<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="$sum_set1" /></xsl:when>
			<xsl:otherwise>100</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:variable name="delitel2">
		<xsl:choose>
			<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="$sum_set2" /></xsl:when>
			<xsl:otherwise>100</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<xsl:variable name="A"><xsl:value-of select="dedek:difference(number(@a), number(@e), number($delitel1), number($delitel2))" /></xsl:variable>
	<xsl:variable name="B"><xsl:value-of select="dedek:difference(number(@b), number(@f), number($delitel1), number($delitel2))" /></xsl:variable>
	<xsl:variable name="C"><xsl:value-of select="dedek:difference(number(@c), number(@g), number($delitel1), number($delitel2))" /></xsl:variable>
	<xsl:variable name="D"><xsl:value-of select="dedek:difference(number(@d), number(@h), number($delitel1), number($delitel2))" /></xsl:variable>
	
	<xsl:variable name="r1"><xsl:value-of select="number($A) + number($B)" /></xsl:variable>
	<xsl:variable name="r2"><xsl:value-of select="number($C) + number($D)" /></xsl:variable>
	<xsl:variable name="c1"><xsl:value-of select="number($A) + number($C)" /></xsl:variable>
	<xsl:variable name="c2"><xsl:value-of select="number($B) + number($D)" /></xsl:variable>
	<xsl:variable name="sum"><xsl:value-of select="number($A) + number($B) + number($C) + number($D)" /></xsl:variable>
	<xsl:variable name="max"><xsl:value-of select="dedek:max4(number($A),number($B),number($C),number($D))" /></xsl:variable>
	
	
	<xsl:variable name="value_A">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:hodnota(number($A), number($sum))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:hodnota(number($A), number($max))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:hodnota(number($A), number($c1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:hodnota(number($A), number($r1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="dedek:hodnota(number($A), number(1))" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="value_B">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:hodnota(number($B), number($sum))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:hodnota(number($B), number($max))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:hodnota(number($B), number($c2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:hodnota(number($B), number($r1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="dedek:hodnota(number($B), number(1))" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="value_C">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:hodnota(number($C), number($sum))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:hodnota(number($C), number($max))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:hodnota(number($C), number($c1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:hodnota(number($C), number($r2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="dedek:hodnota(number($C), number(1))" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="value_D">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:hodnota(number($D), number($sum))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:hodnota(number($D), number($max))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:hodnota(number($D), number($c2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:hodnota(number($D), number($r2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="dedek:hodnota(number($D), number(1))" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
			
		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_4ftgraph">
				<categories id="categories1">
					<category title="{$SuccedentLabel}" id="category1"></category>
					<category title="{$NotSuccedentLabel}" id="category2"></category>
				</categories>			
				<chart title="{$NotAntecedentLabel}" id="chart1" color="{$Chart1Color}">
					<value value="{$value_C}" id="value3"></value>
					<value value="{$value_D}" id="value4"></value>
				</chart>
				<chart title="{$AntecedentLabel}" id="chart2" color="{$Chart2Color}">
					<value value="{$value_A}" id="value1"></value>
					<value value="{$value_B}" id="value2"></value>
				</chart>			
			</graph>
		</paragraph>						
	
	</xsl:template>
      




</xsl:stylesheet>
